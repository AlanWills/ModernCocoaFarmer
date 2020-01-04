using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace MCF.Family
{
	public class Child : ScriptableObject
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("health"), DisplayName("Health")]
		public float Health { get; set; } = 100.000000f;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("safety"), DisplayName("Safety")]
		public float Safety { get; set; } = 100.000000f;

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("education"), DisplayName("Education")]
		public float Education { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("happiness"), DisplayName("Happiness")]
		public float Happiness { get; set; } = 100.000000f;
	}
}
