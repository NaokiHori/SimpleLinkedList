=====
Usage
=====

All functions here are implemented under `src/linked_list.c <https://github.com/NaokiHori/SimpleLinkedList/blob/master/src/linked_list.c>`_.

----------------
llist_get_nitems
----------------

^^^^^^^^^^^
Description
^^^^^^^^^^^

Compute number of items in the given linked list

^^^^^^^^^^
Parameters
^^^^^^^^^^

.. code-block:: c

   int llist_get_nitems(size_t *nitems, llist_t *node_root);

* ``nitems``

   number of items (intent out)

* ``node_root``

   pointer to the root node (intent in)

* return

   ``0`` for normal exit, ``-1`` for abnormal exit (``nitems`` is larger than ``USHRT_MAX``, which is usually ``65535``)

.. details:: More details

   `node_curr` denotes a node which is focued currently.

   Initially we look at the root node.
   Note that the root node can be NULL, i.e., the linked list does not contain any node and the number of items is ``0``.

   .. myliteralinclude:: /../../src/linked_list.c
      :language: c
      :tag: set initial node, root node

   One important feature is that ``node_curr`` is set to ``NULL`` (not allocated) when it is not in the list, which is checked in this loop:

   .. myliteralinclude:: /../../src/linked_list.c
      :language: c
      :tag: move to the next node until finding a node which is not allocated

   .. note::

      When ``nitems`` exceeds ``NITEMS_MAX``, we abort the loop and return the function with failure.
      This is to avoid infinite loops which might happen if the list is circularly linked.

   When the last node is successfully found, get out of the function with success

   .. myliteralinclude:: /../../src/linked_list.c
      :language: c
      :tag: return llist_get_nitems successfully

----------
llist_find
----------

^^^^^^^^^^^
Description
^^^^^^^^^^^

Find a pattern in the given linked list

^^^^^^^^^^
Parameters
^^^^^^^^^^

.. code-block:: c

   int llist_find(int *loc, llist_t *node_root, const void *pattern, const size_t pattern_size);

* ``loc``

   location (``loc``-th node) where the given pattern is found (intent out), ``0`` for root note
   ``-1`` is assigned when the pattern is not found

* ``node_root``

   pointer to the root node (intent in)

* ``pattern``

   pointer to the pattern to be searched (intent in)

* ``pattern_size``

   data size of ``pattern``

* return

  ``0`` for normal exit (**irrespective** to being found or not found), ``-1`` for abnormal exit (e.g., invalid input)

.. details:: More details

   #. Sanitise input

      * ``pattern`` cannot be ``NULL``

      * ``pattern_size`` cannot be ``0``

      They are implemented here

      .. myliteralinclude:: /../../src/linked_list.c
         :language: c
         :tag: 1. error checks

   #. pass

------------
llist_insert
------------

^^^^^^^^^^^
Description
^^^^^^^^^^^

Insert a new node which contains the given data to the given linked list

^^^^^^^^^^
Parameters
^^^^^^^^^^

.. code-block:: c

   int llist_insert(llist_t **node_root, const size_t loc, void *data, const size_t data_size, bool do_copy);

* ``node_root``

   pointer to the root node (intent in/out)

* ``loc``

   location where the new node is inserted, ``0`` for inserting to the head of the list

* ``data``

   pointer to the data to be added (intent in)

* ``data_size``

   data size of ``data``

* ``do_copy``

   copying ``data`` when being stored (using ``memcpy``), or not (just storing the address of the original data)

* return

  ``0`` for normal exit (new node is successfully added), ``-1`` for abnormal exit (e.g., invalid input, too many nodes exist in the linked list)

.. details:: More details

   pass

------------
llist_remove
------------

^^^^^^^^^^^
Description
^^^^^^^^^^^

Remove a new node which contains the given data from the given linked list

^^^^^^^^^^
Parameters
^^^^^^^^^^

.. code-block:: c

   int llist_remove(llist_t **node_root, const size_t loc);

* ``node_root``

   pointer to the root node (intent in/out)

* ``loc``

   location where the node is removed, ``0`` for removing the head of the list

* return

  ``0`` for normal exit (the node is successfully removed), ``-1`` for abnormal exit (e.g., invalid input)

.. details:: More details

   pass

