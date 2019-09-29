using CelesteEngineEditor.Editors;
using MCF.Stats;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ModernCocoaFarmerEditorLibrary.Editors
{
    public class ModifierEditorViewModel : EditorViewModel
    {
        #region Properties and Fields

        public Modifier Modifier { get { return TargetObject as Modifier; } }

        public int Amount
        {
            get { return Modifier.Amount; }
            set { Modifier.Amount = value; }
        }

        public ChangeType ChangeType
        {
            get { return Modifier.ChangeType; }
            set { Modifier.ChangeType = value; }
        }

        public Occurrence Occurrence
        {
            get { return Modifier.Occurrence; }
            set 
            { 
                Modifier.Occurrence = value;
                MonthlyFrequency = MonthlyFrequencyVisible ? MonthlyFrequency : 0;

                NotifyOnPropertyChanged(nameof(MonthlyFrequencyVisible));
            }
        }

        public float MonthlyFrequency
        {
            get { return Modifier.MonthlyFrequency; }
            set { Modifier.MonthlyFrequency = value; }
        }

        public bool MonthlyFrequencyVisible
        {
            get { return Occurrence == Occurrence.Periodic; }
        }

        #endregion

        public ModifierEditorViewModel(Modifier targetModifier) : 
            base(targetModifier)
        {
        }
    }
}
