****************************
Memory leak check - Valgrind
****************************

After all nodes are removed, all heap memories allocated inside the library should be properly freed.
In order to check it, we reply on `Valgrind <https://valgrind.org>`_.
In particular, `src/main.c <https://github.com/NaokiHori/SimpleLinkedList/blob/artifacts/src/main.c>`_ is tested in order to confirm all memories are indeed deallocated at the end of the ``main`` function, which is taken care of by GitHub Actions.

The following is the corresponding part of the memory check in `.github/workflows/ci.yml <https://github.com/NaokiHori/SimpleLinkedList/blob/master/.github/workflows/ci.yml>`_:

.. code-block:: yaml

  valgrind:
    name: Valgrind
    runs-on: ubuntu-latest
    container:
      image: naokihori/alpine-valgrind:1.0
      volumes:
        - :/home
      options: --rm
    steps:
      - name: Checkout repository
        uses: actions/checkout@v1
        with:
          repository: 'NaokiHori/SimpleLinkedList'
          ref: 'master'
      - name: Build and Run Tests
        run: |
          ls -l
          make clean
          make
          valgrind \
            --leak-check=full \
            --error-exitcode=1 \
            --xml=yes \
            --xml-file=valgrind.xml \
            ./a.out
      - name: Upload artifacts
        uses: actions/upload-artifact@v3
        with:
          name: valgrind
          path: valgrind.xml

