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
	public class BuildingInformation : ScriptableObject
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("description"), DisplayName("Description")]
		public string Description { get; set; } = "";

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("months_to_complete"), DisplayName("Months To Complete")]
		public float MonthsToComplete { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(3)]
		[DisplayName("health_modifier")]
		public Modifier Health_modifier { get; set; }

		[Serialize, DisplayPriority(4)]
		[DisplayName("safety_modifier")]
		public Modifier Safety_modifier { get; set; }

		[Serialize, DisplayPriority(5)]
		[DisplayName("education_modifier")]
		public Modifier Education_modifier { get; set; }

		[Serialize, DisplayPriority(6)]
		[DisplayName("happiness_modifier")]
		public Modifier Happiness_modifier { get; set; }

		[Serialize, DisplayPriority(7)]
		[DisplayName("cost_modifier")]
		public Modifier Cost_modifier { get; set; }
	}
}
