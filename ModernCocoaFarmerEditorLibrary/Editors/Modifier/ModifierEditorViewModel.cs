using CelesteEditor.Editors;
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
                PeriodInMonths = PeriodInMonthsVisible ? PeriodInMonths : 0;

                NotifyOnPropertyChanged(nameof(PeriodInMonthsVisible));
            }
        }

        public int PeriodInMonths
        {
            get { return Modifier.PeriodInMonths; }
            set { Modifier.PeriodInMonths = value; }
        }

        public bool PeriodInMonthsVisible
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
