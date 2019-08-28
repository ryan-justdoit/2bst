all:bst avl

CPPFLAGS += -I headers/

bst:bst.c drawtree.c queue.c travel.c
	$(CC) $^ -o $@ $(CPPFLAGS)

avl:avl.c drawtree.c queue.c travel.c
	$(CC) $^ -o $@ $(CPPFLAGS) -DAVL

clean:
	$(RM) bst avl *.html .*.swp

