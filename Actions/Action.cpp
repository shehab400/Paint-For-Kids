#include "Action.h"
#include "..\ApplicationManager.h"

Action::Action(ApplicationManager* pApp) { pManager = pApp; pManager->SetLastUndoRedo(false); }