// Copyright (c) 2022 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0
#include "iceoryx_hoofs/testing/expect_no_death.hpp"
#include "test_cxx_functional_interface_types.hpp"

namespace
{
using namespace test_cxx_functional_interface;
using namespace ::testing;

TYPED_TEST(FunctionalInterface_test, OrElseHasCorrectSignature)
{
    ::testing::Test::RecordProperty("TEST_ID", "ede81b23-cd69-45a4-86aa-b81baa8e281b");
    using Factory = typename TestFixture::TestFactoryType;
    constexpr bool DOES_OR_ELSE_HAVE_A_VALUE = iox::cxx::internal::HasGetErrorMethod<typename Factory::Type>::value;

    EXPECT_THAT(DOES_OR_ELSE_HAVE_A_VALUE, Eq(Factory::EXPECT_OR_ELSE_WITH_VALUE));
}

#define IOX_TEST_FUNCTIONAL_INTERFACE(TestName, variationPoint)                                                        \
    using SutType = typename TestFixture::TestFactoryType::Type;                                                       \
    constexpr bool HAS_GET_ERROR_METHOD = iox::cxx::internal::HasGetErrorMethod<SutType>::value;                       \
    TestName<HAS_GET_ERROR_METHOD>::template performTest<typename TestFixture::TestFactoryType>(                       \
        [](auto& sut, auto callback) { variationPoint.or_else(callback); })

constexpr bool TYPE_HAS_GET_ERROR_METHOD = true;
constexpr bool TYPE_HAS_NO_GET_ERROR_METHOD = false;

template <bool HasError>
struct OrElseIsCalledCorrectlyWhenInvalid;

template <>
struct OrElseIsCalledCorrectlyWhenInvalid<TYPE_HAS_NO_GET_ERROR_METHOD>
{
    template <typename TestFactory, typename OrElseCall>
    static void performTest(const OrElseCall& orElseCall)
    {
        auto sut = TestFactory::createInvalidObject();
        bool wasCallbackCalled = false;
        orElseCall(sut, [&] { wasCallbackCalled = true; });
        EXPECT_TRUE(wasCallbackCalled);
    }
};

template <>
struct OrElseIsCalledCorrectlyWhenInvalid<TYPE_HAS_GET_ERROR_METHOD>
{
    template <typename TestFactory, typename OrElseCall>
    static void performTest(const OrElseCall& orElseCall)
    {
        auto sut = TestFactory::createInvalidObject();
        bool wasCallbackCalled = false;
        orElseCall(sut, [&](auto& arg) {
            wasCallbackCalled = true;
            EXPECT_EQ(arg, TestFactory::usedErrorValue);
        });
        EXPECT_TRUE(wasCallbackCalled);
    }
};

TYPED_TEST(FunctionalInterface_test, OrElseIsCalledCorrectlyWhenInvalid_LValueCase)
{
    ::testing::Test::RecordProperty("TEST_ID", "deddc99a-eec0-466f-a5ba-4018dd372c47");
    IOX_TEST_FUNCTIONAL_INTERFACE(OrElseIsCalledCorrectlyWhenInvalid, sut);
}

TYPED_TEST(FunctionalInterface_test, OrElseIsCalledCorrectlyWhenInvalid_ConstLValueCase)
{
    ::testing::Test::RecordProperty("TEST_ID", "851ca90c-4433-4a6d-9a7b-08cdca78b3c4");
    IOX_TEST_FUNCTIONAL_INTERFACE(OrElseIsCalledCorrectlyWhenInvalid, const_cast<const SutType&>(sut));
}

TYPED_TEST(FunctionalInterface_test, OrElseIsCalledCorrectlyWhenInvalid_RValueCase)
{
    ::testing::Test::RecordProperty("TEST_ID", "eb4d7b93-201e-44d9-8482-af23a6ae854b");
    IOX_TEST_FUNCTIONAL_INTERFACE(OrElseIsCalledCorrectlyWhenInvalid, std::move(sut));
}

TYPED_TEST(FunctionalInterface_test, OrElseIsCalledCorrectlyWhenInvalid_ConstRValueCase)
{
    ::testing::Test::RecordProperty("TEST_ID", "1c85d1bb-7934-43ad-b08e-87cafa5dce26");
    IOX_TEST_FUNCTIONAL_INTERFACE(OrElseIsCalledCorrectlyWhenInvalid, std::move(const_cast<const SutType&>(sut)));
}

template <bool HasError>
struct OrElseIsNotCalledWhenValid;

template <>
struct OrElseIsNotCalledWhenValid<TYPE_HAS_NO_GET_ERROR_METHOD>
{
    template <typename TestFactory, typename OrElseCall>
    static void performTest(const OrElseCall& orElseCall)
    {
        auto sut = TestFactory::createValidObject();
        bool wasCallbackCalled = false;
        orElseCall(sut, [&] { wasCallbackCalled = true; });
        EXPECT_FALSE(wasCallbackCalled);
    }
};

template <>
struct OrElseIsNotCalledWhenValid<TYPE_HAS_GET_ERROR_METHOD>
{
    template <typename TestFactory, typename OrElseCall>
    static void performTest(const OrElseCall& orElseCall)
    {
        auto sut = TestFactory::createValidObject();
        bool wasCallbackCalled = false;
        orElseCall(sut, [&](auto&) { wasCallbackCalled = true; });
        EXPECT_FALSE(wasCallbackCalled);
    }
};

TYPED_TEST(FunctionalInterface_test, OrElseIsNotCalledWhenValid_LValueCase)
{
    ::testing::Test::RecordProperty("TEST_ID", "d9dcf588-f15b-4065-8427-cbf7b6873038");
    IOX_TEST_FUNCTIONAL_INTERFACE(OrElseIsNotCalledWhenValid, sut);
}

TYPED_TEST(FunctionalInterface_test, OrElseIsNotCalledWhenValid_ConstLValueCase)
{
    ::testing::Test::RecordProperty("TEST_ID", "4a061c42-eb93-4fc4-ad30-a117f8703659");
    IOX_TEST_FUNCTIONAL_INTERFACE(OrElseIsNotCalledWhenValid, const_cast<const SutType&>(sut));
}

TYPED_TEST(FunctionalInterface_test, OrElseIsNotCalledWhenValid_RValueCase)
{
    ::testing::Test::RecordProperty("TEST_ID", "2e371008-c74c-408b-ae4f-70329b487874");
    IOX_TEST_FUNCTIONAL_INTERFACE(OrElseIsNotCalledWhenValid, std::move(sut));
}

TYPED_TEST(FunctionalInterface_test, OrElseIsNotCalledWhenValid_ConstRValueCase)
{
    ::testing::Test::RecordProperty("TEST_ID", "6e58eee9-9c99-4ade-b144-d83821a25170");
    IOX_TEST_FUNCTIONAL_INTERFACE(OrElseIsNotCalledWhenValid, std::move(const_cast<const SutType&>(sut)));
}

template <bool HasValue>
struct OrElseDoesNotCrashWithNullFunction;

template <>
struct OrElseDoesNotCrashWithNullFunction<TYPE_HAS_NO_GET_ERROR_METHOD>
{
    template <typename TestFactory, typename OrElseCall>
    static void performTest(const OrElseCall& callOrElse)
    {
        auto sut = TestFactory::createInvalidObject();
        EXPECT_NO_DEATH([&] { callOrElse(sut, iox::cxx::function_ref<void()>()); });
    }
};

template <>
struct OrElseDoesNotCrashWithNullFunction<TYPE_HAS_GET_ERROR_METHOD>
{
    template <typename TestFactory, typename OrElseCall>
    static void performTest(const OrElseCall& callOrElse)
    {
        auto sut = TestFactory::createInvalidObject();
        EXPECT_NO_DEATH([&] { callOrElse(sut, iox::cxx::function_ref<void(typename TestFactory::error_t&)>()); });
    }
};

template <bool HasValue>
struct OrElseDoesNotCrashWithNullFunction_Const;

template <>
struct OrElseDoesNotCrashWithNullFunction_Const<TYPE_HAS_NO_GET_ERROR_METHOD>
{
    template <typename TestFactory, typename OrElseCall>
    static void performTest(const OrElseCall& callOrElse)
    {
        auto sut = TestFactory::createInvalidObject();
        EXPECT_NO_DEATH([&] { callOrElse(sut, iox::cxx::function_ref<void()>()); });
    }
};

template <>
struct OrElseDoesNotCrashWithNullFunction_Const<TYPE_HAS_GET_ERROR_METHOD>
{
    template <typename TestFactory, typename OrElseCall>
    static void performTest(const OrElseCall& callOrElse)
    {
        auto sut = TestFactory::createInvalidObject();
        EXPECT_NO_DEATH([&] { callOrElse(sut, iox::cxx::function_ref<void(const typename TestFactory::error_t&)>()); });
    }
};

TYPED_TEST(FunctionalInterface_test, OrElseDoesNotCrashWithNullFunction_LValueCase)
{
    ::testing::Test::RecordProperty("TEST_ID", "661a087d-90ee-4b27-9af4-b4d4b211adeb");
    IOX_TEST_FUNCTIONAL_INTERFACE(OrElseDoesNotCrashWithNullFunction, sut);
}

TYPED_TEST(FunctionalInterface_test, OrElseDoesNotCrashWithNullFunction_ConstLValueCase)
{
    ::testing::Test::RecordProperty("TEST_ID", "5913ed24-cb6e-47e6-a0af-c0650cc642a0");
    IOX_TEST_FUNCTIONAL_INTERFACE(OrElseDoesNotCrashWithNullFunction_Const, const_cast<const SutType&>(sut));
}

TYPED_TEST(FunctionalInterface_test, OrElseDoesNotCrashWithNullFunction_RValueCase)
{
    ::testing::Test::RecordProperty("TEST_ID", "38ee906c-1314-440a-9328-976362555db0");
    IOX_TEST_FUNCTIONAL_INTERFACE(OrElseDoesNotCrashWithNullFunction, std::move(sut));
}

TYPED_TEST(FunctionalInterface_test, OrElseDoesNotCrashWithNullFunction_ConstRValueCase)
{
    ::testing::Test::RecordProperty("TEST_ID", "0e2ed65f-a130-4de8-8757-3585cd77cc75");
    IOX_TEST_FUNCTIONAL_INTERFACE(OrElseDoesNotCrashWithNullFunction_Const, std::move(const_cast<const SutType&>(sut)));
}
#undef IOX_TEST_FUNCTIONAL_INTERFACE
} // namespace
