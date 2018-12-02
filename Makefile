all:
	clang++ -std=gnu++2a obv_inner_product.c -c && clang++ -std=gnu++2a obv_inner_product.o -o obv_inner_product
