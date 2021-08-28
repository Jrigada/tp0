SHARED_MODULE = Utils
MODULES = client server

.PHONY: $(SHARED_MODULE) $(MODULES)

all: $(SHARED_MODULE) $(MODULES)

Utils:
	$(MAKE) -C $@

client: Utils
	$(MAKE) -C $@

server: Utils
	$(MAKE) -C $@

Config_updater:
	$(MAKE) -C $@

clean:
	$(MAKE) -C $(SHARED_MODULE) clean
	$(foreach module, $(MODULES), $(MAKE) -C $(module) clean &&) true