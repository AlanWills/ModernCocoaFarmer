using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace MCF.Stats
{
	public class ChildModifier : Modifier
	{
		[Serialize, DisplayPriority(5)]
		[XmlAttribute("applies_to_all_children"), DisplayName("Applies To All Children")]
		public bool AppliesToAllChildren { get; set; } = false;
	}
}
