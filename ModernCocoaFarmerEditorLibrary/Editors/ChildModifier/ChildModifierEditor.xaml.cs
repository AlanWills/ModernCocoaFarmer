using CelesteEngineEditor.Attributes;
using CelesteEngineEditor.Editors;
using MCF.Stats;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ModernCocoaFarmerEditorLibrary.Editors
{
    /// <summary>
    /// Interaction logic for ChildModifierEditor.xaml
    /// </summary>
    [CustomEditor(typeof(ChildModifier), "Child Modifier Editor")]
    public partial class ChildModifierEditor : Editor
    {
        #region Properties and Fields

        private ModifierEditor ModifierEditor { get; set; }

        #endregion

        public ChildModifierEditor(ChildModifier modifier) :
            base(new ChildModifierEditorViewModel(modifier))
        {
            InitializeComponent();

            ModifierEditor = new ModifierEditor(ViewModel as ModifierEditorViewModel);
            Content.Content = ModifierEditor;
        }
    }
}
