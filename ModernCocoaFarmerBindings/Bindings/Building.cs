using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace MCF.Buildings
{
	public class Building : ScriptableObject
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("name"), DisplayName("Name")]
		public string Name { get; set; } = "";

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("description"), DisplayName("Description")]
		public string Description { get; set; } = "";
	}
}
