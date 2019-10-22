#include "stdafx.h"

#include "Persistence/DataStore.h"

using namespace MCF::Persistence;


namespace TestMCF
{
	CELESTE_TEST_CLASS(TestDataStore)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Constructor_CreatesEmptyDataStore)
  {
    DataStore dataStore;

    Assert::AreEqual(static_cast<size_t>(0), dataStore.getSize());
  }

#pragma endregion

#pragma region Get Size Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_GetSize_DataStoreIsEmpty_ReturnsZero)
  {
    DataStore dataStore;

    Assert::AreEqual(static_cast<size_t>(0), dataStore.getSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_GetSize_DataStoreIsNotEmpty_ReturnsCorrectSize)
  {
    DataStore dataStore;
    dataStore.setBool("Test", true);
    dataStore.setBool("Test2", false);

    Assert::AreEqual(static_cast<size_t>(2), dataStore.getSize());
  }

#pragma endregion

#pragma region Has Data Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_HasData_InputtingNonExistentKey_ReturnsFalse)
  {
    DataStore dataStore;

    Assert::AreEqual(static_cast<size_t>(0), dataStore.getSize());
    Assert::IsFalse(dataStore.hasData("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_HasData_InputtingExistentKey_ReturnsTrue)
  {
    DataStore dataStore;
    dataStore.setBool("Test", true);

    Assert::AreEqual(static_cast<size_t>(1), dataStore.getSize());
    Assert::IsTrue(dataStore.hasData("Test"));
  }

#pragma endregion

#pragma region Get Bool Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_GetBool_InputtingNonExistentKey_ReturnsDefaultValue)
  {
    DataStore dataStore;

    Assert::IsFalse(dataStore.hasData("Test"));
    Assert::IsTrue(dataStore.getBool("Test", true));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_GetBool_InputtingExistentKey_ReturnsStoredValue)
  {
    DataStore dataStore;
    dataStore.setBool("Test", false);

    Assert::IsTrue(dataStore.hasData("Test"));
    Assert::IsFalse(dataStore.getBool("Test", true));
  }

#pragma endregion

#pragma region Set Bool Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_SetBool_InputtingExistentKey_ModifiesStoredValue)
  {
    DataStore dataStore;
    dataStore.setBool("Test", false);

    Assert::IsTrue(dataStore.hasData("Test"));
    Assert::IsFalse(dataStore.getBool("Test", true));

    dataStore.setBool("Test", true);

    Assert::IsTrue(dataStore.hasData("Test"));
    Assert::IsTrue(dataStore.getBool("Test", false));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_SetBool_InputtingNonExistentKey_AddsStoredValue)
  {
    DataStore dataStore;
    dataStore.setBool("Test", false);

    Assert::IsTrue(dataStore.hasData("Test"));
    Assert::IsFalse(dataStore.getBool("Test", true));
  }

#pragma endregion

#pragma region Serialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Serialize_DataStoreEmpty_DoesNotModifyInputtedElement)
  {
    DataStore dataStore;

    Assert::AreEqual(static_cast<size_t>(0), dataStore.getSize());

    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement());

    dataStore.serialize(*element);

    Assert::IsNull(element->FirstChildElement());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Serialize_DataStoreNotEmpty_AddsCorrectNumberOfChildElements)
  {
    DataStore dataStore;
    dataStore.setBool("Test", false);
    dataStore.setBool("Test2", true);

    Assert::AreEqual(static_cast<size_t>(2), dataStore.getSize());

    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement());

    dataStore.serialize(*element);

    Assert::IsNotNull(element->FirstChildElement());
    Assert::IsNotNull(element->FirstChildElement()->NextSiblingElement());
  }

#pragma region Serialize Bool Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Serialize_DataStoreHasBoolValue_AddsCorrectDataTypeAttribute_ToChildElement)
  {
    DataStore dataStore;
    dataStore.setBool("Test", false);

    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement());

    dataStore.serialize(*element);
    XMLElement* valueElement = element->FirstChildElement();

    Assert::IsNotNull(valueElement);
    Assert::AreEqual(static_cast<int>(DataStore::DataType::kBool), valueElement->IntAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Serialize_DataStoreHasBoolValue_AddsCorrectKeyAttribute_ToChildElement)
  {
    DataStore dataStore;
    dataStore.setBool("Test", false);

    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement());

    dataStore.serialize(*element);
    XMLElement* valueElement = element->FirstChildElement();

    Assert::IsNotNull(valueElement);
    Assert::AreEqual("Test", valueElement->Attribute(DataStore::KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Serialize_DataStoreHasFalseBoolValue_AddsFalseAttribute_ToChildElement)
  {
    DataStore dataStore;
    dataStore.setBool("Test", false);

    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement());

    dataStore.serialize(*element);
    XMLElement* valueElement = element->FirstChildElement();

    Assert::IsNotNull(valueElement);
    Assert::IsFalse(valueElement->BoolAttribute(DataStore::VALUE_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Serialize_DataStoreHasTrueBoolValue_AddsTrueAttribute_ToChildElement)
  {
    DataStore dataStore;
    dataStore.setBool("Test", true);

    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement());

    dataStore.serialize(*element);
    XMLElement* valueElement = element->FirstChildElement();

    Assert::IsNotNull(valueElement);
    Assert::IsTrue(valueElement->BoolAttribute(DataStore::VALUE_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma endregion

#pragma region Deserialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithNoChildren_ReturnsEmptyDataStore)
	{
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement());

    std::unique_ptr<DataStore> store = DataStore::deserialize(*element);
	}

#pragma region Deserialize Bool Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithBoolChildren_AllChildrenValid_ReturnsDataStoreWithCorrectData)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* bool1 = document.NewElement("Bool1");
    bool1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 0);
    bool1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool1");
    bool1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, true);

    XMLElement* bool2 = document.NewElement("Bool2");
    bool2->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 0);
    bool2->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool2");
    bool2->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, false);
    
    element->InsertFirstChild(bool1);
    element->InsertFirstChild(bool2);

    std::unique_ptr<DataStore> store = DataStore::deserialize(*element);

    Assert::IsTrue(store->hasData("TestBool1"));
    Assert::IsTrue(store->hasData("TestBool2"));
    Assert::IsTrue(store->getBool("TestBool1"));
    Assert::IsFalse(store->getBool("TestBool2"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithBoolChildren_ChildWithMissingDataTypeAttribute_DoesNotAddEntryToReturnedDataStore)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* bool1 = document.NewElement("Bool1");
    bool1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 0);
    bool1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool1");
    bool1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, true);

    XMLElement* bool2 = document.NewElement("Bool2");
    bool2->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool2");
    bool2->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, false);

    element->InsertFirstChild(bool1);
    element->InsertFirstChild(bool2);

    std::unique_ptr<DataStore> store = DataStore::deserialize(*element);

    Assert::IsTrue(store->hasData("TestBool1"));
    Assert::IsFalse(store->hasData("TestBool2"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithBoolChildren_ChildWithMissingKeyAttribute_DoesNotAddEntryToReturnedDataStore)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* bool1 = document.NewElement("Bool1");
    bool1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 0);
    bool1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool1");
    bool1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, true);

    XMLElement* bool2 = document.NewElement("Bool2");
    bool2->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 0);
    bool2->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, false);

    element->InsertFirstChild(bool1);
    element->InsertFirstChild(bool2);

    std::unique_ptr<DataStore> store = DataStore::deserialize(*element);

    Assert::IsTrue(store->hasData("TestBool1"));
    Assert::IsFalse(store->hasData("TestBool2"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithBoolChildren_ChildWithMissingValueAttribute_DoesNotAddEntryToReturnedDataStore)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* bool1 = document.NewElement("Bool1");
    bool1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 0);
    bool1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool1");
    bool1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, true);

    XMLElement* bool2 = document.NewElement("Bool2");
    bool2->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 0);
    bool2->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool2");

    element->InsertFirstChild(bool1);
    element->InsertFirstChild(bool2);

    std::unique_ptr<DataStore> store = DataStore::deserialize(*element);

    Assert::IsTrue(store->hasData("TestBool1"));
    Assert::IsFalse(store->hasData("TestBool2"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithBoolChildren_ChildWithInvalidDataTypeAttribute_DoesNotAddEntryToReturnedDataStore)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* bool1 = document.NewElement("Bool1");
    bool1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 0);
    bool1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool1");
    bool1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, true);

    XMLElement* bool2 = document.NewElement("Bool2");
    bool2->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 100);
    bool2->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool2");
    bool2->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, false);

    element->InsertFirstChild(bool1);
    element->InsertFirstChild(bool2);

    std::unique_ptr<DataStore> store = DataStore::deserialize(*element);

    Assert::IsTrue(store->hasData("TestBool1"));
    Assert::IsFalse(store->hasData("TestBool2"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithBoolChildren_ChildWithDuplicateKeyAttribute_DoesNotAddEntryToReturnedDataStore)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* bool1 = document.NewElement("Bool1");
    bool1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 0);
    bool1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool1");
    bool1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, true);

    XMLElement* bool2 = document.NewElement("Bool2");
    bool2->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 0);
    bool2->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool1");
    bool2->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, false);

    element->InsertFirstChild(bool1);
    element->InsertFirstChild(bool2);

    std::unique_ptr<DataStore> store = DataStore::deserialize(*element);

    Assert::IsTrue(store->hasData("TestBool1"));
    Assert::IsFalse(store->hasData("TestBool2"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithBoolChildren_ChildWithInvalidValueAttribute_DoesNotAddEntryToReturnedDataStore)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* bool1 = document.NewElement("Bool1");
    bool1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 0);
    bool1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool1");
    bool1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, true);

    XMLElement* bool2 = document.NewElement("Bool2");
    bool2->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 0);
    bool2->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool2");
    bool2->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    element->InsertFirstChild(bool1);
    element->InsertFirstChild(bool2);

    std::unique_ptr<DataStore> store = DataStore::deserialize(*element);

    Assert::IsTrue(store->hasData("TestBool1"));
    Assert::IsFalse(store->hasData("TestBool2"));
  }

#pragma endregion

#pragma endregion

	};
}
