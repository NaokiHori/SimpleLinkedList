################
SimpleLinkedList
################

|License|_

|DocDeployment|_

|WorkflowStatus|_ |UnitTest|_ |MemoryLeak|_

|LastCommit|_

.. |License| image:: https://img.shields.io/github/license/NaokiHori/SimpleLinkedList
.. _License: https://opensource.org/licenses/MIT

.. |DocDeployment| image:: https://github.com/NaokiHori/SimpleLinkedList/actions/workflows/documentation.yml/badge.svg
.. _DocDeployment: https://naokihori.github.io/SimpleLinkedList/

.. |WorkflowStatus| image:: https://github.com/NaokiHori/SimpleLinkedList/actions/workflows/ci.yml/badge.svg?branch=master
.. _WorkflowStatus: https://github.com/NaokiHori/SimpleLinkedList/actions/workflows/ci.yml

.. |UnitTest| image:: https://github.com/NaokiHori/SimpleLinkedList/blob/artifacts/.github/workflows/artifacts/badge_cunit.svg
.. _UnitTest: https://github.com/NaokiHori/Alpine-Dockerfiles/tree/cunit

.. |MemoryLeak| image:: https://github.com/NaokiHori/SimpleLinkedList/blob/artifacts/.github/workflows/artifacts/badge_valgrind.svg
.. _MemoryLeak: https://github.com/NaokiHori/Alpine-Dockerfiles/tree/valgrind

.. |LastCommit| image:: https://img.shields.io/github/last-commit/NaokiHori/SimpleLinkedList/master
.. _LastCommit: https://github.com/NaokiHori/SimpleLinkedList/commits/master

.. image:: https://github.com/NaokiHori/SimpleLinkedList/blob/master/coverimage.png

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

Badges are partially created using `Shields.io <https://shields.io>`_.

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

``src/linked_list.c`` includes the implementations, while ``include/linked_list.h`` contains their declarations.
No installation is needed; After copying a header file ``include/linked_list.h`` and its source file ``src/linked_list.c`` to the corresponding places of your project, one is ready for using all functions implemented.

An example can be found in ``src/main.c``, where all functions are extensively used.
Also please refer to the `documentation <https://naokihori.github.io/SimpleLinkedList>`_.

******
Others
******

This project is mainly for my personal use.
The main objective was to study CI/CD of C projects and related stuffs (GitHub Actions).

