/*
    APE Network Library
    Copyright (C) 2010-2013 Anthony Catel <paraboul@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __APE_ARRAY_H
#define __APE_ARRAY_H

#include "ape_pool.h"
#include "ape_buffer.h"

typedef ape_pool_list_t ape_array_t;

#define APE_ARRAY_USED_SLOT (1 << 1)
#define APE_ARRAY_VAL_BUF (1 << 2)
#define APE_ARRAY_VAL_INT (1 << 3)
#define APE_ARRAY_HASHED  (1 << 4)

typedef enum {
    APE_ARRAY_HASH,
    APE_ARRAY_LIST
} ape_array_index_e;

struct _ape_array_item {
    /* inherit from ape_pool_t (same first sizeof(ape_pool_t) bytes memory-print) */
    ape_pool_t pool;
    buffer *key;
    //buffer *val;
} typedef ape_array_item_t;

#ifdef __cplusplus
extern "C" {
#endif

ape_array_t *ape_array_new(size_t n);
ape_array_item_t *ape_array_lookup_item(ape_array_t *array,
        const char *key, int klen);
buffer *ape_array_lookup(ape_array_t *array, const char *key, int klen);
buffer *ape_array_lookup_nocase(ape_array_t *array, const char *key, int klen);
void *ape_array_lookup_data(ape_array_t *array, const char *key, int klen);

ape_array_item_t *ape_array_add_b(ape_array_t *array, buffer *key, buffer *value);
ape_array_item_t *ape_array_add_n(ape_array_t *array, const char *key, int klen, const char *value, int vlen);
ape_array_item_t *ape_array_add_camelkey_n(ape_array_t *array, const char *key,
        int klen, const char *value, int vlen);
ape_array_item_t *ape_array_add(ape_array_t *array, const char *key, const char *value);
void ape_array_destroy(ape_array_t *array);
ape_array_item_t *ape_array_add_ptr(ape_array_t *array, buffer *key, void *ptr);
ape_array_item_t *ape_array_add_ptrn(ape_array_t *array, const char *key, int klen, void *ptr);


#ifdef __cplusplus
}
#endif


#define APE_A_FOREACH(_array, _key, _val) \
        ape_array_item_t *__array_item; \
        for (__array_item = (ape_array_item_t *)_array->head; __array_item != NULL; __array_item = (ape_array_item_t *)__array_item->pool.next) \
            if ((__array_item->pool.flags & APE_ARRAY_USED_SLOT) && (_key = __array_item->key) && (_val = __array_item->pool.ptr.buf)) \

#endif

// vim: ts=4 sts=4 sw=4 et

