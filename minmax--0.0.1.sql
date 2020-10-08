-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION minmax" to load this file. \quit

CREATE OR REPLACE FUNCTION _final_minmax(NUMERIC[])
   RETURNS text 
immutable
language plpgsql
AS $$
declare 
   min NUMERIC;
   max NUMERIC;
BEGIN
   min := (SELECT MIN(val)
   FROM (
     SELECT val
     FROM unnest($1) val
     ORDER BY 1
   ) sub);
   
   max := (SELECT MAX(val)
   FROM (
     SELECT val
     FROM unnest($1) val
     ORDER BY 1
   ) sub);
return min || ' -> ' || max;
END;
$$;
 
CREATE AGGREGATE min_to_max(NUMERIC) (
  SFUNC=array_append,
  STYPE=NUMERIC[],
  FINALFUNC=_final_minmax,
  INITCOND='{}'
);


