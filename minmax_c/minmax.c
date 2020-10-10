#include "postgres.h"

#include "catalog/pg_type.h"
#include "fmgr.h"
#include "miscadmin.h"
#include "utils/array.h"
#include "utils/builtins.h"
#include "utils/geo_decls.h"
#include "utils/int8.h"
#include "utils/ruleutils.h"


#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif



PG_FUNCTION_INFO_V1(minmax_sfunc);

Datum
minmax_sfunc(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);
    Datum      *values;
    int         nelement;
    int         i;
    int         min, max;
    if (ARR_ELEMTYPE(array) != INT4OID)
        ereport(ERROR,
                (errcode(ERRCODE_DATATYPE_MISMATCH),
                 errmsg("only interger array is suported")));
    deconstruct_array(array,
                      INT4OID, sizeof(int), true, i,
                      &values, NULL, &nelement);
    if (nelement == 0)
        PG_RETURN_NULL();
    min = max = DatumGetInt32(values[0]);
    for (i = 1; i < nelement; i++)
    {
        if (min > DatumGetInt32(values[i]))
            min = DatumGetInt32(values[i]);
        if (max < DatumGetInt32(values[i]))
            max = DatumGetInt32(values[i]);
    }
    PG_RETURN_TEXT_P(cstring_to_text(psprintf("%d -> %d", min, max)));
}




/*
PG_FUNCTION_INFO_V1(minmax_sfunc);

Datum
minmax_sfunc(PG_FUNCTION_ARGS)
{
	Point *new_agg_state[] = (Point *) palloc(sizeof(Point));
	double el = PG_GETARG_FLOAT8(1);
	bool isnull = PG_ARGISNULL(0);
	int nelement;
  	if(isnull) {
    		new_agg_state->x = el;
    		new_agg_state->y = el;
   	PG_RETURN_POINT_P(new_agg_state);
  	}


	Point *agg_state = PG_GETARG_POINT_P(0);
	
	new_agg_state->x = new_agg_state->y = el;
	nelement = = sizeof(el)/sizeof(int);
    for (i = 1; i < nelement; i++)
    {
        if (new_agg_state->x > DatumGetInt32(el[i]))
            new_agg_state->x = DatumGetInt32(el[i]);
        if (new_agg_state->y < DatumGetInt32(el[i]))
            new_agg_state->y = DatumGetInt32(el[i]);
    }
//    PG_RETURN_POINT_P(cstring_to_text(psprintf("%d -> %d", new_agg_state->x, new_agg_state->y)));
  	PG_RETURN_POINT_P(new_agg_state);
}


PG_FUNCTION_INFO_V1(minmax_sfunc);

Datum
minmax_sfunc(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);
    Datum      *values;
    int	nelement;
    int	i;  
    int	min, max;
    if (ARR_ELEMTYPE(array) != INT4OID)
        ereport(ERROR,
                (errcode(ERRCODE_DATATYPE_MISMATCH),
                 errmsg("only interger array is suported")));
    deconstruct_array(array,
                      INT4OID, sizeof(int), true, i,
                      &values, NULL, &nelement);
    if (nelement == 0)
        PG_RETURN_NULL();
    min = max = DatumGetInt32(values[0]);
    for (i = 1; i < nelement; i++)
    {   
        if (min > DatumGetInt32(values[i]))
            min = DatumGetInt32(values[i]);
        if (max < DatumGetInt32(values[i]))
            max = DatumGetInt32(values[i]);
    }   
    PG_RETURN_TEXT_P(cstring_to_text(psprintf("%d -> %d", min, max)));
} 

*/

/*
PG_FUNCTION_INFO_V1(minmax_sfunc);

Datum
minmax_sfunc(PG_FUNCTION_ARGS)
{
    ArrayType *a = PG_GETARG_ARRAYTYPE_P(0);
    Datum  *datums;
    bool   *nulls;
    int     count;
    int16   elemWidth;
    Oid     elemType = ARR_ELEMTYPE(a);
    bool    elemTypeByVal, isNull;
    char    elemAlignmentCode;
    int     result = 0;
    //HeapTupleHeader lt;
    short   field;
    int	     i, min, max;

    if (ARR_NDIM(a) > 1)
        ereport(ERROR, (errcode(ERRCODE_ARRAY_SUBSCRIPT_ERROR), errmsg("1-dimensional array needed")));

    get_typlenbyvalalign(elemType, &elemWidth, &elemTypeByVal, &elemAlignmentCode);
    deconstruct_array(a, elemType, elemWidth, elemTypeByVal, elemAlignmentCode, &datums, &nulls, &count);

    for (i = 0; i < count; i++)
    {
	if (count == 0)
        	PG_RETURN_NULL();
    	min = max = DatumGetInt32(datums[0]);
    	for (i = 1; i < count; i++)
	{
        	if (min > DatumGetInt32(datums[i]))
            		min = DatumGetInt32(datums[i]);
        	if (max < DatumGetInt32(datums[i]))
            		max = DatumGetInt32(datums[i]);
    	}
    }
    PG_RETURN_INT32(min);
    //PG_RETURN_TEXT_P(cstring_to_text(psprintf("%d -> %d", min, max)));
    //PG_GETARG_ARRAYTYPE_P(cstring_to_text(psprintf("%d -> %d", min, max)));

}

*/

