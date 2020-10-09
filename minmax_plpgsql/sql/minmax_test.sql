
CREATE TABLE test(id int, sal numeric);
INSERT into test values(generate_series(1,10),generate_series(1.1,10));
SELECT min_to_max(sal) FROM test;
SELECT min_to_max(val) FROM (VALUES(0),(3),(6),(7),(9),(1),(17)) t(val);
