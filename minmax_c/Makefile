EXTENSION = minmax        # the extensions name
DATA = minmax--0.0.1.sql  # script files to install
REGRESS = minmax_test     # our test script file (without extension)
MODULES = minmax          # our c module file to build
# postgres build stuff
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
