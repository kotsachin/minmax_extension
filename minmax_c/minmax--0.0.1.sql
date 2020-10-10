-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION minmax" to load this file. \quit
--CREATE FUNCTION base36_encode(integer) RETURNS text
--AS '$libdir/minmax'
--LANGUAGE C IMMUTABLE STRICT;

create function
  minmax_sfunc( point, float8 )
returns
  point
as
  'minmax.so', 'minmax_sfunc'
language
  c
immutable;

create function minmax_finalfunc(minmax_state point)
returns float8
immutable
language plpgsql
as $$
begin
  return minmax_state[1];
end;
$$;

create aggregate min_to_max(float8)
(
    sfunc = minmax_sfunc,
    stype = point,
    finalfunc = minmax_finalfunc
);

