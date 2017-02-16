.PHONY: config
config:
	bash scripts/config.sh
	@echo '[  OK  ] Workspaces are built'

.PHONY: all
all: config
	ls build/ | xargs -I '{name}' make -C 'build/{name}'
