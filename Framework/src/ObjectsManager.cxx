///
/// \file   ObjectsManager.cxx
/// \author Barthelemy von Haller
///

#include "Common/Exceptions.h"
#include "QualityControl/ObjectsManager.h"
#include "QualityControl/QcInfoLogger.h"

using namespace o2::quality_control::core;
using namespace AliceO2::Common;
using namespace std;

namespace o2 {
namespace quality_control {
namespace core {

ObjectsManager::ObjectsManager(TaskConfig &taskConfig) : mTaskName(taskConfig.taskName)
{
  startPublishing(&mObjectsList, MonitorObject::SYSTEM_OBJECT_PUBLICATION_LIST);
}

ObjectsManager::~ObjectsManager()
{
  for (auto &mMonitorObject : mMonitorObjects) {
    delete mMonitorObject.second;
  }
  mMonitorObjects.clear();
}

void ObjectsManager::startPublishing(TObject *object, std::string objectName)
{
  std::string nonEmptyName = objectName.empty() ? object->GetName() : objectName;
  auto *newObject = new MonitorObject(nonEmptyName, object, mTaskName);
  newObject->setIsOwner(false);
  mMonitorObjects[nonEmptyName] = newObject;

  //update index
  UpdateIndex(nonEmptyName);
}

void ObjectsManager::UpdateIndex(const string &nonEmptyName)
{
  string newString = this->mObjectsList.GetString().Data();
  newString += nonEmptyName;
  newString += ",";
  this->mObjectsList.SetString(newString.c_str());
}

void ObjectsManager::setQuality(std::string objectName, Quality quality)
{
  MonitorObject *mo = getMonitorObject(objectName);
  mo->setQuality(quality);
}

Quality ObjectsManager::getQuality(std::string objectName)
{
  MonitorObject *mo = getMonitorObject(objectName);
  return mo->getQuality();
}

void ObjectsManager::addCheck(const std::string &objectName, const std::string &checkName,
                              const std::string &checkClassName, const std::string &checkLibraryName)
{
  MonitorObject *mo = getMonitorObject(objectName);
  mo->addCheck(checkName, checkClassName, checkLibraryName);

  QcInfoLogger::GetInstance() << "Added check : " << objectName << " , " << checkName << " , " << checkClassName
                              << " , " << checkLibraryName << infologger::endm;
}

MonitorObject *ObjectsManager::getMonitorObject(std::string objectName)
{
  if (mMonitorObjects.count(objectName) > 0) {
    return mMonitorObjects[objectName];
  } else {
    BOOST_THROW_EXCEPTION(ObjectNotFoundError() << errinfo_object_name(objectName));
  }
}

TObject *ObjectsManager::getObject(std::string objectName)
{
  MonitorObject *mo = getMonitorObject(objectName);
  return mo->getObject();
}

void ObjectsManager::addCheck(const TObject *object, const std::string &checkName, const std::string &checkClassName,
                              const std::string &checkLibraryName)
{
  addCheck(object->GetName(), checkName, checkClassName, checkLibraryName);
}

} // namespace core
} // namespace quality_control
} // namespace o2
