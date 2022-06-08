********************
Unit testing - CUnit
********************

As explained in :ref:`the linked list <linked_list>`, there are mainly four functions, whose behaviours should be extensively tested (unit testings).a
In this project, we use `CUnit <http://cunit.sourceforge.net>`_ as a unit test framework.

All test cases can be found under `cunit directory <https://github.com/NaokiHori/SimpleLinkedList/tree/master/cunit>`_.

The following is the corresponding part of the unit test in `.github/workflows/ci.yml <https://github.com/NaokiHori/SimpleLinkedList/blob/master/.github/workflows/ci.yml>`_:

.. code-block:: yaml

  cunit:
    name: Cunit
    runs-on: ubuntu-latest
    container:
      image: naokihori/alpine-cunit:1.0
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
          cd cunit; make clean; make
          for f in *.out;
          do
            ./$f
          done
      - name: Merge xml files
        run: |
          cd cunit
          apk add npm
          npm install -g junit-report-merger
          jrm ../cunit.xml *.xml
      - name: Upload artifacts
        uses: actions/upload-artifact@v3
        with:
          name: cunit
          path: cunit.xml

