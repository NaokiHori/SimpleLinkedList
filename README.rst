################
SimpleLinkedList
################

|License|_ |WorkflowStatus|_ |UnitTest|_ |MemoryLeak|_ |LastCommit|_

.. |License| image:: https://img.shields.io/github/license/NaokiHori/SimpleLinkedList
.. _License: https://opensource.org/licenses/MIT

.. |WorkflowStatus| image:: https://img.shields.io/github/workflow/status/NaokiHori/SimpleLinkedList/CI/master.svg
.. _WorkflowStatus: https://github.com/NaokiHori/SimpleLinkedList/actions

.. |UnitTest| image:: https://github.com/NaokiHori/SimpleLinkedList/blob/artifacts/.github/workflows/artifacts/badge_cunit.svg
.. _UnitTest: https://github.com/NaokiHori/Alpine-Dockerfiles/tree/cunit

.. |MemoryLeak| image:: https://github.com/NaokiHori/SimpleLinkedList/blob/artifacts/.github/workflows/artifacts/badge_valgrind.svg
.. _MemoryLeak: https://github.com/NaokiHori/Alpine-Dockerfiles/tree/valgrind

.. |LastCommit| image:: https://img.shields.io/github/last-commit/NaokiHori/SimpleLinkedList/master
.. _LastCommit: https://github.com/NaokiHori/SimpleLinkedList/commits/master

Linked list implementation in C99 with the following (minimal) functions

* Insertion

* Removal

* Search

* Counting number of items

All functions are tested using `CUint <http://cunit.sourceforge.net>`_, and proper memory allocations and deallocations are checked using `Valgrind <https://valgrind.org>`_ (and reflected as badges at the top).
These tests are automated using `GitHub Actions <https://docs.github.com/en/actions>`_ under Ubuntu and Alpine Linux environments.
The following actions are used

* `actions/checkout <https://github.com/actions/checkout>`_

* `actions/upload-artifact <https://github.com/actions/upload-artifact>`_

* `actions/download-artifact <https://github.com/actions/download-artifact>`_

* `EnricoMi/publish-unit-test-result-action <https://github.com/EnricoMi/publish-unit-test-result-action>`_

* `ad-m/github-push-action <https://github.com/ad-m/github-push-action>`_

*Concise, consistent, and legible badges* are created using `Shields.io <https://shields.io>`_.

**********
Dependency
**********

* Linked list

   C compiler (later than C99), no dependency on external libraries

* Unit test

   CUint, in addition to C compiler

* Memory leak check

   Valgrind, in addition to C compiler

Docker images for CUint and Valgrind can be found here:

* https://github.com/NaokiHori/Alpine-Dockerfiles

* https://hub.docker.com/r/naokihori/alpine-cunit

* https://hub.docker.com/r/naokihori/alpine-valgrind

*****
Usage
*****

===========
Linked list
===========

``src/linked_list.c`` includes the implementations, while ``include/linked_list.h`` contains their declarations.
No installation is needed; After copying a header file ``include/linked_list.h`` and its source file ``src/linked_list.c`` to the corresponding places of your project, one is ready for using all functions implemented.

An example can be found in ``src/main.c``, where all functions are extensively used.

--------------------
Simple documentation
--------------------

Imagine we have two sets of data

.. code-block:: c

   int data0[5] = {3, 1, 4, 1, 5};
   double data1[3] = {9.2, 6.5, 3.5};

One initialises the root node (empty linked list) by

.. code-block:: c

   llist_t *node_root = NULL;

to which a new node containing ``data0`` can be appended as

.. code-block:: c

   llist_insert(
     &node_root,    /* address of the root node */
     0,             /* location where new node is inserted */
     data0,         /* address of the data to be added */
     sizeof(int)*5, /* total data size */
     true           /* copy (i.e. memcpy) whole data or not */
   );

To order to add the second data as the second node, one would do

.. code-block:: c

   llist_insert(
     &node_root,       /* address of the root node */
     1,                /* location where new node is inserted */
     data1,            /* address of the data to be added */
     sizeof(double)*3, /* total data size */
     true              /* copy (i.e. memcpy) whole data or not */
   );

while one can replace the root node (second node comes in front of the first one) instead by

.. code-block:: c

   llist_insert(
     &node_root,       /* address of the root node */
     0,                /* location where new node is inserted */
     data1,            /* address of the data to be added */
     sizeof(double)*3, /* total data size */
     true              /* copy (i.e. memcpy) whole data or not */
   );

Generally, one can insert a node at location `i` (remind that index starts from 0) in the same manner by

.. code-block:: c

   llist_insert(
     &node_root, /* address of the root node */
     i,          /* location where new node is inserted */
     ...,        /* address of the data to be added */
     ...,        /* total data size */
     ...         /* copy (i.e. memcpy) whole data or not */
   );

Note that, when *the location* is equal to *the number of nodes*, the new node is added to the end of the linked list.
When *the location* is larger than *the number of nodes*, the list is unchanged and an errorcode -1 is returned.

Similarly one can remove a node by

.. code-block:: c

   llist_remove(
     &node_root, /* address of the root node */
     i           /* location where node is removed */
   );

Note that, when *the location* is equal to *the number of nodes* **-1**, the last node is removed from the linked list.
When *the location* is larger than *the number of nodes* **-1**, the list is unchanged and an errorcode -1 is returned.

One might be interested in the number of all connected nodes ``nitems`` in a linked list whose root node is ``node_root``, which can be checked by

.. code-block:: c

   size_t nitems;
   llist_get_nitems(
      &nitems,  /* result, number of nodes */
      node_root /* address of the root node */
   );

Or sometimes we would like to know whether a specific data exists in the linked list, and its location if there is.
This can be achieved by

.. code-block:: c

   llist_find(
      &loc,        /* result, location where the data is contained */
      node_root,   /* address of the root node */
      pattern,     /* data which is expected to match */
      pattern_size /* data size of pattern */
   );

Note that this function returns 0 (success) even when the pattern is not found, but instead -1 is assigned to *loc*.
Failure (-1) is returned for severer errors, such as when invalid arguments are passed (e.g. null pointer to *pattern*).

******
Others
******

This project is mainly for my personal use.
The main objective was to study CI/CD of C projects and related stuffs (GitHub Actions).

