using CelesteEngineEditor.Editors;
using MCF.Stats;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ModernCocoaFarmerEditorLibrary.Editors
{
    public class ChildModifierEditorViewModel : ModifierEditorViewModel
    {
        #region Properties and Fields

        public ChildModifier ChildModifier { get { return TargetObject as ChildModifier; } }

        public bool AppliesToAllChildren
        {
            get { return ChildModifier.AppliesToAllChildren; }
            set { ChildModifier.AppliesToAllChildren = value; }
        }

        #endregion

        public ChildModifierEditorViewModel(ChildModifier targetModifier) : 
            base(targetModifier)
        {
        }
    }
}
