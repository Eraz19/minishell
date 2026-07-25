#include "libft.h"
#include "error.h"
#include "utils.h"

t_error	vector_deep_dup(
			t_vector *dst,
			const t_vector *src,
			t_dup_callback dup_callback,
			t_free_callback free_callback)
{
	size_t		i;
	void		*dst_item;
	const void	*src_item;
	t_error		err;

	(void)vector_init(dst, src->item_size, 0);
	i = 0;
	while (i < src->len)
	{
		if (dst->cap == dst->len && !vector_grow(dst))
		{
			err = error_sys();
			return (vector_free(dst, free_callback), err);
		}
		dst_item = dst->data + (i * dst->item_size);
		src_item = src->data + (i * src->item_size);
		err = dup_callback(dst_item, src_item);
		if (err.type)
			return (vector_free(dst, free_callback), err);
		dst->len++;
	}
	return (error(ERR_NO));
}
