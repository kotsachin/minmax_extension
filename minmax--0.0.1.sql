-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION minmax" to load this file. \quit

/*
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
*/

CREATE OR REPLACE FUNCTION _final_minmax(arr NUMERIC[])
   RETURNS text
immutable
language plpgsql
AS $$
declare
   min NUMERIC;
   max NUMERIC;
   len INT;
BEGIN
   len = array_length(arr, 1);
   IF len = 0 THEN
   	return NULL;
   END IF;
	min := arr[1];
	max := arr[1];
   FOR i IN 2..len LOOP
   	IF (min > arr[i]) THEN
		min := arr[i];
	ELSIF (max < arr[i]) THEN
		max := arr[i];
	END IF;
   END LOOP;
	return min || ' -> ' || max;
END;
$$;
 
CREATE AGGREGATE min_to_max(NUMERIC) (
  SFUNC=array_append,
  STYPE=NUMERIC[],
  FINALFUNC=_final_minmax,
  INITCOND='{}'
);


