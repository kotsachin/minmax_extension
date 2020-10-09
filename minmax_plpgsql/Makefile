EXTENSION = minmax        # the extensions name
DATA = minmax--0.0.1.sql  # script files to install
REGRESS = minmax_test
# postgres build stuff
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

EXTRA_CLEAN = minmax.control minmax--0.0.1.sql
