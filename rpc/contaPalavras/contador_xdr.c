/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "contador.h"

bool_t
xdr_Palavra (XDR *xdrs, Palavra *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->texto, 128))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Resposta (XDR *xdrs, Resposta *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->resultado, 1024))
		 return FALSE;
	return TRUE;
}
