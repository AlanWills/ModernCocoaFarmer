using MCF.Stats;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace MCF.Locations
{
	public class LocationInformation : ScriptableObject
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("description"), DisplayName("Description")]
		public string Description { get; set; } = "";

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("months_to_complete"), DisplayName("Months To Complete")]
		public float MonthsToComplete { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(3)]
		[DisplayName("HealthModifier")]
		public ChildModifier HealthModifier { get; set; }

		[Serialize, DisplayPriority(4)]
		[DisplayName("SafetyModifier")]
		public ChildModifier SafetyModifier { get; set; }

		[Serialize, DisplayPriority(5)]
		[DisplayName("EducationModifier")]
		public ChildModifier EducationModifier { get; set; }

		[Serialize, DisplayPriority(6)]
		[DisplayName("HappinessModifier")]
		public ChildModifier HappinessModifier { get; set; }

		[Serialize, DisplayPriority(7)]
		[DisplayName("MoneyModifier")]
		public Modifier MoneyModifier { get; set; }
	}
}
