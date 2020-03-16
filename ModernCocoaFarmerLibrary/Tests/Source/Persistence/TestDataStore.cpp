#include "UtilityHeaders/UnitTestHeaders.h"
#include "Persistence/DataStore.h"

using namespace tinyxml2;
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
    dataStore.set<bool>("Test", true);
    dataStore.set<bool>("Test2", false);

    Assert::AreEqual(static_cast<size_t>(2), dataStore.getSize());
  }

#pragma endregion

#pragma region Has Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Has_InputtingNonExistentKey_ReturnsFalse)
  {
    DataStore dataStore;

    Assert::AreEqual(static_cast<size_t>(0), dataStore.getSize());
    Assert::IsFalse(dataStore.has("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Has_InputtingExistentKey_ReturnsTrue)
  {
    DataStore dataStore;
    dataStore.set<bool>("Test", true);

    Assert::AreEqual(static_cast<size_t>(1), dataStore.getSize());
    Assert::IsTrue(dataStore.has("Test"));
  }

#pragma endregion

#pragma region Is Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Is_InputtingNonExistentKey_ReturnsFalse)
  {
    DataStore dataStore;

    Assert::IsFalse(dataStore.has("Test"));
    Assert::IsFalse(dataStore.is<bool>("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Is_InputtingExistentKey_ToNonMatchingType_ReturnsFalse)
  {
    DataStore dataStore;
    dataStore.set<int>("Test", 5);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsFalse(dataStore.is<bool>("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Is_InputtingExistentKey_ToMatchingType_ReturnsTrue)
  {
    DataStore dataStore;
    dataStore.set<bool>("Test", true);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsTrue(dataStore.is<bool>("Test"));
  }

#pragma endregion

#pragma region Get Tests

#pragma region Bool

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Get_Bool_InputtingNonExistentKey_ReturnsDefaultValue)
  {
    DataStore dataStore;

    Assert::IsFalse(dataStore.has("Test"));
    Assert::IsTrue(dataStore.get<bool>("Test", true));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Get_Bool_InputtingExistentKey_ToNonBoolType_ReturnsStoredValue)
  {
    DataStore dataStore;
    dataStore.set<int>("Test", 5);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsFalse(dataStore.is<bool>("Test"));
    Assert::IsTrue(dataStore.get<bool>("Test", true));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Get_Bool_InputtingExistentKey_ToBoolType_ReturnsStoredValue)
  {
    DataStore dataStore;
    dataStore.set<bool>("Test", false);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsTrue(dataStore.is<bool>("Test"));
    Assert::IsFalse(dataStore.get<bool>("Test", true));
  }

#pragma endregion

#pragma region Int

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Get_Int_InputtingNonExistentKey_ReturnsDefaultValue)
  {
    DataStore dataStore;

    Assert::IsFalse(dataStore.has("Test"));
    Assert::AreEqual(5, dataStore.get<int>("Test", 5));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Get_Int_InputtingExistentKey_ToNonIntType_ReturnsStoredValue)
  {
    DataStore dataStore;
    dataStore.set<bool>("Test", true);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsFalse(dataStore.is<int>("Test"));
    Assert::AreEqual(5, dataStore.get<int>("Test", 5));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Get_Int_InputtingExistentKey_ToIntType_ReturnsStoredValue)
  {
    DataStore dataStore;
    dataStore.set<int>("Test", 10);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsTrue(dataStore.is<int>("Test"));
    Assert::AreEqual(10, dataStore.get<int>("Test", 5));
  }

#pragma endregion

#pragma endregion

#pragma region Set Tests

#pragma region Bool

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Set_Bool_InputtingExistentKey_ToBoolValue_ModifiesStoredValue)
  {
    DataStore dataStore;
    dataStore.set<bool>("Test", false);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsTrue(dataStore.is<bool>("Test"));
    Assert::IsFalse(dataStore.get<bool>("Test", true));

    dataStore.set<bool>("Test", true);

    Assert::IsTrue(dataStore.get<bool>("Test", false));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Set_Bool_InputtingExistentKey_ToBoolValue_ReturnsTrue)
  {
    DataStore dataStore;
    dataStore.set<bool>("Test", false);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsTrue(dataStore.is<bool>("Test"));
    Assert::IsFalse(dataStore.get<bool>("Test", true));
    Assert::IsTrue(dataStore.set<bool>("Test", true));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Set_Bool_InputtingExistentKey_ToNonBoolValue_DoesNotModifyStoredValue)
  {
    DataStore dataStore;
    dataStore.set<int>("Test", 5);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsFalse(dataStore.is<bool>("Test"));
    Assert::AreEqual(5, dataStore.get<int>("Test", 0));

    dataStore.set<bool>("Test", false);

    Assert::AreEqual(5, dataStore.get<int>("Test", 0));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Set_Bool_InputtingExistentKey_ToNonBoolValue_ReturnsFalse)
  {
    DataStore dataStore;
    dataStore.set<int>("Test", 5);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsFalse(dataStore.is<bool>("Test"));
    Assert::AreEqual(5, dataStore.get<int>("Test", 0));
    Assert::IsFalse(dataStore.set<bool>("Test", false));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Set_Bool_InputtingNonExistentKey_AddsStoredValue)
  {
    DataStore dataStore;

    Assert::IsFalse(dataStore.has("Test"));

    dataStore.set<bool>("Test", false);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsTrue(dataStore.is<bool>("Test"));
    Assert::IsFalse(dataStore.get<bool>("Test", true));
  }

#pragma endregion

#pragma region Int

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Set_Int_InputtingExistentKey_ToIntValue_ModifiesStoredValue)
  {
    DataStore dataStore;
    dataStore.set<int>("Test", 5);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsTrue(dataStore.is<int>("Test"));
    Assert::AreEqual(5, dataStore.get<int>("Test", 0));

    dataStore.set<int>("Test", 10);

    Assert::AreEqual(10, dataStore.get<int>("Test", 0));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Set_Int_InputtingExistentKey_ToBoolValue_ReturnsTrue)
  {
    DataStore dataStore;
    dataStore.set<int>("Test", 5);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsTrue(dataStore.is<int>("Test"));
    Assert::AreEqual(5, dataStore.get<int>("Test", 0));
    Assert::IsTrue(dataStore.set<int>("Test", 10));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Set_Int_InputtingExistentKey_ToNonBoolValue_DoesNotModifyStoredValue)
  {
    DataStore dataStore;
    dataStore.set<int>("Test", 5);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsTrue(dataStore.is<int>("Test"));
    Assert::AreEqual(5, dataStore.get<int>("Test", 0));

    dataStore.set<bool>("Test", false);

    Assert::AreEqual(5, dataStore.get<int>("Test", 0));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Set_Int_InputtingExistentKey_ToNonBoolValue_ReturnsFalse)
  {
    DataStore dataStore;
    dataStore.set<int>("Test", 5);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsTrue(dataStore.is<int>("Test"));
    Assert::AreEqual(5, dataStore.get<int>("Test", 0));
    Assert::IsFalse(dataStore.set<bool>("Test", false));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Set_Int_InputtingNonExistentKey_AddsStoredValue)
  {
    DataStore dataStore;

    Assert::IsFalse(dataStore.has("Test"));

    dataStore.set<int>("Test", 5);

    Assert::IsTrue(dataStore.has("Test"));
    Assert::IsTrue(dataStore.is<int>("Test"));
    Assert::AreEqual(5, dataStore.get<int>("Test", 0));
  }

#pragma endregion

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
    dataStore.set<bool>("Test", false);
    dataStore.set<int>("Test2", 5);

    Assert::AreEqual(static_cast<size_t>(2), dataStore.getSize());

    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement());

    dataStore.serialize(*element);

    Assert::IsNotNull(element->FirstChildElement());
    Assert::IsNotNull(element->FirstChildElement()->NextSiblingElement());
  }

#pragma region Bool

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Serialize_DataStoreHasBoolValue_AddsCorrectDataTypeAttribute_ToChildElement)
  {
    DataStore dataStore;
    dataStore.set<bool>("Test", false);

    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement());

    dataStore.serialize(*element);
    XMLElement* valueElement = element->FirstChildElement();

    Assert::IsNotNull(valueElement);
    Assert::AreEqual(0, valueElement->IntAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Serialize_DataStoreHasBoolValue_AddsCorrectKeyAttribute_ToChildElement)
  {
    DataStore dataStore;
    dataStore.set<bool>("Test", false);

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
    dataStore.set<bool>("Test", false);

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
    dataStore.set<bool>("Test", true);

    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement());

    dataStore.serialize(*element);
    XMLElement* valueElement = element->FirstChildElement();

    Assert::IsNotNull(valueElement);
    Assert::IsTrue(valueElement->BoolAttribute(DataStore::VALUE_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Int

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Serialize_DataStoreHasIntValue_AddsCorrectDataTypeAttribute_ToChildElement)
  {
    DataStore dataStore;
    dataStore.set<int>("Test", 5);

    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement());

    dataStore.serialize(*element);
    XMLElement* valueElement = element->FirstChildElement();

    Assert::IsNotNull(valueElement);
    Assert::AreEqual(1, valueElement->IntAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Serialize_DataStoreHasIntValue_AddsCorrectKeyAttribute_ToChildElement)
  {
    DataStore dataStore;
    dataStore.set<int>("Test", 5);

    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement());

    dataStore.serialize(*element);
    XMLElement* valueElement = element->FirstChildElement();

    Assert::IsNotNull(valueElement);
    Assert::AreEqual("Test", valueElement->Attribute(DataStore::KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Serialize_DataStoreHasIntValue_AddsCorrectIntAttribute_ToChildElement)
  {
    DataStore dataStore;
    dataStore.set<int>("Test", -10);

    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement());

    dataStore.serialize(*element);
    XMLElement* valueElement = element->FirstChildElement();

    Assert::IsNotNull(valueElement);
    Assert::AreEqual(-10, valueElement->IntAttribute(DataStore::VALUE_ATTRIBUTE_NAME));
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

    DataStore store = DataStore::deserialize(*element);

    Assert::AreEqual(static_cast<size_t>(0), store.getSize());
	}

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithChildren_AllChildrenValid_ReturnsDataStoreWithCorrectData)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* bool1 = document.NewElement("Bool1");
    bool1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 0);
    bool1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestBool1");
    bool1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, true);

    XMLElement* int2 = document.NewElement("Int2");
    int2->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 1);
    int2->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt2");
    int2->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, 5);

    element->InsertFirstChild(bool1);
    element->InsertEndChild(int2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestBool1"));
    Assert::IsTrue(store.is<bool>("TestBool1"));
    Assert::IsTrue(store.get<bool>("TestBool1", false));
    Assert::IsTrue(store.has("TestInt2"));
    Assert::IsTrue(store.is<int>("TestInt2"));
    Assert::AreEqual(5, store.get<int>("TestInt2", 0));
  }

#pragma region Bool

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
    element->InsertEndChild(bool2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestBool1"));
    Assert::IsTrue(store.is<bool>("TestBool1")); 
    Assert::IsTrue(store.get<bool>("TestBool1", false));
    Assert::IsTrue(store.has("TestBool2"));
    Assert::IsTrue(store.is<bool>("TestBool2"));
    Assert::IsFalse(store.get<bool>("TestBool2", true));
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
    element->InsertEndChild(bool2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestBool1"));
    Assert::IsFalse(store.has("TestBool2"));
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
    element->InsertEndChild(bool2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestBool1"));
    Assert::IsFalse(store.has("TestBool2"));
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
    element->InsertEndChild(bool2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestBool1"));
    Assert::IsFalse(store.has("TestBool2"));
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
    element->InsertEndChild(bool2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestBool1"));
    Assert::IsFalse(store.has("TestBool2"));
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
    element->InsertEndChild(bool2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestBool1"));
    Assert::IsFalse(store.has("TestBool2"));
    Assert::IsTrue(store.get<bool>("TestBool1"));
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
    element->InsertEndChild(bool2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestBool1"));
    Assert::IsFalse(store.has("TestBool2"));
  }

#pragma endregion

#pragma region Int

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithIntChildren_AllChildrenValid_ReturnsDataStoreWithCorrectData)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* int1 = document.NewElement("Int1");
    int1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 1);
    int1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt1");
    int1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, -10);

    XMLElement* int2 = document.NewElement("Int2");
    int2->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 1);
    int2->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt2");
    int2->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, 5);

    element->InsertFirstChild(int1);
    element->InsertEndChild(int2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestInt1"));
    Assert::IsTrue(store.is<int>("TestInt1"));
    Assert::AreEqual(-10, store.get<int>("TestInt1", 0));
    Assert::IsTrue(store.has("TestInt2"));
    Assert::IsTrue(store.is<int>("TestInt2"));
    Assert::AreEqual(5, store.get<int>("TestInt2", 0));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithIntChildren_ChildWithMissingDataTypeAttribute_DoesNotAddEntryToReturnedDataStore)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* int1 = document.NewElement("Int1");
    int1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 1);
    int1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt1");
    int1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, -10);

    XMLElement* int2 = document.NewElement("Int2");
    int2->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt2");
    int2->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, 5);

    element->InsertFirstChild(int1);
    element->InsertEndChild(int2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestInt1"));
    Assert::IsFalse(store.has("TestInt2"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithIntChildren_ChildWithMissingKeyAttribute_DoesNotAddEntryToReturnedDataStore)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* int1 = document.NewElement("Int1");
    int1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 1);
    int1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt1");
    int1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, -10);

    XMLElement* int2 = document.NewElement("Int2");
    int2->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 1);
    int2->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, 5);

    element->InsertFirstChild(int1);
    element->InsertEndChild(int2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestInt1"));
    Assert::IsFalse(store.has("TestInt2"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithIntChildren_ChildWithMissingValueAttribute_DoesNotAddEntryToReturnedDataStore)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* int1 = document.NewElement("Int1");
    int1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 1);
    int1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt1");
    int1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, -10);

    XMLElement* int2 = document.NewElement("Int2");
    int2->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 1);
    int2->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt2");

    element->InsertFirstChild(int1);
    element->InsertEndChild(int2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestInt1"));
    Assert::IsFalse(store.has("TestInt2"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithIntChildren_ChildWithInvalidDataTypeAttribute_DoesNotAddEntryToReturnedDataStore)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* int1 = document.NewElement("Int1");
    int1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 1);
    int1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt1");
    int1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, -10);

    XMLElement* int2 = document.NewElement("Int2");
    int2->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 100);
    int2->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt2");
    int2->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, -10);

    element->InsertFirstChild(int1);
    element->InsertEndChild(int2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestInt1"));
    Assert::IsFalse(store.has("TestInt2"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithIntChildren_ChildWithDuplicateKeyAttribute_DoesNotAddEntryToReturnedDataStore)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* int1 = document.NewElement("Int1");
    int1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 1);
    int1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt1");
    int1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, -10);

    XMLElement* int2 = document.NewElement("Int2");
    int2->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 1);
    int2->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt1");
    int2->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, 10);

    element->InsertFirstChild(int1);
    element->InsertEndChild(int2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestInt1"));
    Assert::IsFalse(store.has("TestInt2"));
    Assert::AreEqual(-10, store.get<int>("TestInt1"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataStore_Deserialize_InputtingXmlElementWithIntChildren_ChildWithInvalidValueAttribute_DoesNotAddEntryToReturnedDataStore)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* int1 = document.NewElement("Int1");
    int1->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 1);
    int1->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt1");
    int1->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, -10);

    XMLElement* int2 = document.NewElement("Int2");
    int2->SetAttribute(DataStore::DATA_TYPE_ATTRIBUTE_NAME, 1);
    int2->SetAttribute(DataStore::KEY_ATTRIBUTE_NAME, "TestInt2");
    int2->SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    element->InsertFirstChild(int1);
    element->InsertEndChild(int2);

    DataStore store = DataStore::deserialize(*element);

    Assert::IsTrue(store.has("TestInt1"));
    Assert::IsFalse(store.has("TestInt2"));
  }

#pragma endregion

#pragma endregion

	};
}
