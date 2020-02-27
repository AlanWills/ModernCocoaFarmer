﻿using CelesteEditor.Attributes;
using CelesteEditor.Editors;
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
    /// Interaction logic for ModifierEditor.xaml
    /// </summary>
    [CustomEditor(typeof(Modifier), "Modifier Editor")]
    public partial class ModifierEditor : Editor
    {
        public ModifierEditor(Modifier modifier) :
            base(new ModifierEditorViewModel(modifier))
        {
            InitializeComponent();
        }

        public ModifierEditor(ModifierEditorViewModel viewModel) :
            base(viewModel)
        {
            InitializeComponent();
        }
    }
}
