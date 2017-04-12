#!/usr/bin/env stack
{- stack exec ghc
--package process
--package system-filepath
--package turtle
--package text
--
-o dbt
-}

{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE LambdaCase #-}

import Prelude hiding (FilePath)

import qualified Filesystem.Path.CurrentOS as Path
import Data.Char
import Data.List
import qualified Data.Text as Text
import qualified Data.Text.IO as Text
import qualified System.IO as SysIO
import qualified System.Process as Proc
import System.Environment
import Turtle

workspacePath :: Text -> FilePath
workspacePath ws = "build" </> Path.fromText ws

makeWorkspace :: Text -> IO ()
makeWorkspace ws = do
    let dir = workspacePath ws
    ready <- testdir dir
    when (not ready) (mkdir dir)

build :: Text -> IO ()
build ws = do
    -- TODO Support Linux
    let Right textOut = Path.toText $ workspacePath ws </> Path.fromText ws <.> "exe"
    let src = "src" </> Path.fromText ws <.> "cpp"
    let Right textSrc = Path.toText $ src
    optsText <- strict $ limitWhile (("///" `Text.isPrefixOf`) . lineToText) (input src)
    let opts = ((Text.dropWhile isSpace . Text.drop 3) <$> (Text.lines optsText)) :: [Text]
        (args, deps) = partition ("-" `Text.isPrefixOf`) opts
        allOpts = args ++ ["-o", textOut, textSrc] ++ deps
    Text.hPutStrLn SysIO.stderr $ "$ g++ " <> Text.unwords allOpts
    proc "g++" allOpts empty >>= \case
        ExitSuccess -> err "Success!"
        ExitFailure{} -> err "Failure!"

prompt :: IO Text
prompt = promptWith ""

promptWith :: Text -> IO Text
promptWith prefix = do
    liftIO $ do
        Text.hPutStr SysIO.stderr (prefix <> "> ")
        SysIO.hFlush SysIO.stderr
    readline >>= \case
        Nothing -> err "" >> exit ExitSuccess
        Just u -> pure (lineToText u)

getTask :: IO (Text, Text)
getTask = arguments >>= \case
    [ws] -> pure (ws, "build")
    [ws, cmd] -> pure (ws, cmd)
    _ -> do
        err "Usage: dbt problem-name [command]"
        exit (ExitFailure 1)

startShell :: Text -> IO ()
startShell ws =
    shell ("start cmd /k cd build/" <> ws) empty >>= \case
        ExitSuccess -> pure ()
        ExitFailure{} -> err "Why did starting the shell fail?"

main :: IO ()
main = getTask >>= \(ws, cmd) -> do
    makeWorkspace ws
    case cmd of
        "build" -> build ws
        "shell" -> startShell ws
        "test" -> startShell ws