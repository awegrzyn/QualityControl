///
/// \file   SpyMainFrame.h
/// \author Barthelemy von Haller
///

#ifndef QUALITYCONTROL_SRC_QCSPY_H_
#define QUALITYCONTROL_SRC_QCSPY_H_

//std
#include <map>
// ROOT
#include <TGMdiMainFrame.h>
#include <TGStatusBar.h>
#include <TGButton.h>
#include <TGLabel.h>
#include <TGMenu.h>
#include <TRootEmbeddedCanvas.h>
#include <TGTextEntry.h>
#include <TGCanvas.h>
#include <TGComboBox.h>
#include "QualityControl/Quality.h"

namespace o2 {
namespace quality_control {
namespace repository {
class DatabaseInterface;
}
namespace gui {

class SpyDevice;

class SpyMainFrame: public TGMainFrame
{
  public:
    /**
     * \param spyDevice Needed to connect the buttons to their slot in the Device that acts as Controller.
     */
    SpyMainFrame(SpyDevice *spyDevice, std::string configurationSource);
    ~SpyMainFrame() override;

    enum MenuIDs
    {
      FILE_EXIT,
    };

    void closeWindow();
    void menuHandler(Int_t id);
    void updateList(std::string name/*, o2::quality_control::core::Quality quality*/, std::string taskName = "");
    /**
     * \param listName The name as it appears in the list and that might be different from obj->GetName()
     */
    void displayObject(TObject *obj);
    void start(); // slot
    void stop(); // slot
    void displayObject(const char* objectName); // slot
    void ToggleSource(Bool_t on);
    bool dbIsSelected();
    void dbDisplayObject(std::string objectName);
    void dbRun();

  private:
    void constructWindow();
    void removeAllObjectsButtons();

    TGHorizontalFrame *mBottomButtonFrame;
    TGHorizontalFrame *mObjectsBrowserFrame;
    TGMenuBar* mMenuBar;
    TGVerticalFrame *mObjectsListFrame;
    TGCanvas *mScrollObjectsListContainer;
    TRootEmbeddedCanvas *mCanvas;
    std::map<std::string, TGButton*> mMapButtons;
    // For the form
    TGButtonGroup *mRadioButtonGroup;
    TGRadioButton *mSourceDb, *mSourceFairmq;
    TGLabel *mSourceLabel, *mTypeLabel, *mAddressLabel;
    TGTextEntry *mAddressField;
    TGTextButton *mStartButton, *mStopButton;
    TGComboBox *mTypeField;
    TGLabel *mTaskLabel;
    TGTextEntry *mTaskField;

    SpyDevice* mController;
    TObject* mDrawnObject;
    o2::quality_control::repository::DatabaseInterface* mDbInterface;

    bool mDbRunning;

  ClassDef(SpyMainFrame,1);
};

} /* namespace gui */
} /* namespace QualityControl */
} /* namespace o2 */

#endif /* QUALITYCONTROL_SRC_QCSPY_H_ */
