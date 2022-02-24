#Archivos de google test

INCLUDEPATH += $$PWD/googletest/include
INCLUDEPATH += $$PWD/googlemock/include
INCLUDEPATH += $$PWD/googletest
INCLUDEPATH += $$PWD/googlemock

SOURCES += \
    $$PWD/../gtest/googlemock/src/gmock-all.cc \
    $$PWD/../gtest/googlemock/src/gmock-cardinalities.cc \
    $$PWD/../gtest/googlemock/src/gmock-internal-utils.cc \
    $$PWD/../gtest/googlemock/src/gmock-matchers.cc \
    $$PWD/../gtest/googlemock/src/gmock-spec-builders.cc \
    $$PWD/../gtest/googlemock/src/gmock.cc \
    $$PWD/../gtest/googletest/src/gtest-all.cc \
    $$PWD/../gtest/googletest/src/gtest-death-test.cc \
    $$PWD/../gtest/googletest/src/gtest-filepath.cc \
    $$PWD/../gtest/googletest/src/gtest-matchers.cc \
    $$PWD/../gtest/googletest/src/gtest-port.cc \
    $$PWD/../gtest/googletest/src/gtest-printers.cc \
    $$PWD/../gtest/googletest/src/gtest-test-part.cc \
    $$PWD/../gtest/googletest/src/gtest-typed-test.cc \
    $$PWD/../gtest/googletest/src/gtest.cc

HEADERS += \
    $$PWD/../gtest/googlemock/include/gmock/internal/custom/gmock-generated-actions.h \
    $$PWD/../gtest/googlemock/include/gmock/internal/custom/gmock-matchers.h \
    $$PWD/../gtest/googlemock/include/gmock/internal/custom/gmock-port.h \
    $$PWD/../gtest/googlemock/include/gmock/internal/gmock-internal-utils.h \
    $$PWD/../gtest/googlemock/include/gmock/internal/gmock-port.h \
    $$PWD/../gtest/googlemock/include/gmock/internal/gmock-pp.h \
    $$PWD/../gtest/googlemock/include/gmock/gmock-actions.h \
    $$PWD/../gtest/googlemock/include/gmock/gmock-cardinalities.h \
    $$PWD/../gtest/googlemock/include/gmock/gmock-function-mocker.h \
    $$PWD/../gtest/googlemock/include/gmock/gmock-generated-actions.h \
    $$PWD/../gtest/googlemock/include/gmock/gmock-matchers.h \
    $$PWD/../gtest/googlemock/include/gmock/gmock-more-actions.h \
    $$PWD/../gtest/googlemock/include/gmock/gmock-more-matchers.h \
    $$PWD/../gtest/googlemock/include/gmock/gmock-nice-strict.h \
    $$PWD/../gtest/googlemock/include/gmock/gmock-spec-builders.h \
    $$PWD/../gtest/googlemock/include/gmock/gmock.h \
    $$PWD/../gtest/googletest/include/gtest/internal/custom/gtest-port.h \
    $$PWD/../gtest/googletest/include/gtest/internal/custom/gtest-printers.h \
    $$PWD/../gtest/googletest/include/gtest/internal/custom/gtest.h \
    $$PWD/../gtest/googletest/include/gtest/internal/gtest-death-test-internal.h \
    $$PWD/../gtest/googletest/include/gtest/internal/gtest-filepath.h \
    $$PWD/../gtest/googletest/include/gtest/internal/gtest-internal.h \
    $$PWD/../gtest/googletest/include/gtest/internal/gtest-param-util.h \
    $$PWD/../gtest/googletest/include/gtest/internal/gtest-port-arch.h \
    $$PWD/../gtest/googletest/include/gtest/internal/gtest-port.h \
    $$PWD/../gtest/googletest/include/gtest/internal/gtest-string.h \
    $$PWD/../gtest/googletest/include/gtest/internal/gtest-type-util.h \
    $$PWD/../gtest/googletest/include/gtest/gtest-death-test.h \
    $$PWD/../gtest/googletest/include/gtest/gtest-matchers.h \
    $$PWD/../gtest/googletest/include/gtest/gtest-message.h \
    $$PWD/../gtest/googletest/include/gtest/gtest-param-test.h \
    $$PWD/../gtest/googletest/include/gtest/gtest-printers.h \
    $$PWD/../gtest/googletest/include/gtest/gtest-spi.h \
    $$PWD/../gtest/googletest/include/gtest/gtest-test-part.h \
    $$PWD/../gtest/googletest/include/gtest/gtest-typed-test.h \
    $$PWD/../gtest/googletest/include/gtest/gtest.h \
    $$PWD/../gtest/googletest/include/gtest/gtest_pred_impl.h \
    $$PWD/../gtest/googletest/include/gtest/gtest_prod.h \
    $$PWD/../gtest/googletest/src/gtest-internal-inl.h
