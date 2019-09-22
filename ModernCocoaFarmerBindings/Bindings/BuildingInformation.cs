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
		[XmlAttribute("health_change"), DisplayName("Health Change")]
		public float HealthChange { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("safety_change"), DisplayName("Safety Change")]
		public float SafetyChange { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("education_change"), DisplayName("Education Change")]
		public float EducationChange { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(5)]
		[XmlAttribute("happiness_change"), DisplayName("Happiness Change")]
		public float HappinessChange { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(6)]
		[XmlAttribute("is_health_change_for_all_children"), DisplayName("Is Health Change For All Children")]
		public bool IsHealthChangeForAllChildren { get; set; } = false;

		[Serialize, DisplayPriority(7)]
		[XmlAttribute("is_safety_change_for_all_children"), DisplayName("Is Safety Change For All Children")]
		public bool IsSafetyChangeForAllChildren { get; set; } = false;

		[Serialize, DisplayPriority(8)]
		[XmlAttribute("is_education_change_for_all_children"), DisplayName("Is Education Change For All Children")]
		public bool IsEducationChangeForAllChildren { get; set; } = false;

		[Serialize, DisplayPriority(9)]
		[XmlAttribute("is_happiness_change_for_all_children"), DisplayName("Is Happiness Change For All Children")]
		public bool IsHappinessChangeForAllChildren { get; set; } = false;

		[Serialize, DisplayPriority(10)]
		[XmlAttribute("cost"), DisplayName("Cost")]
		public int Cost { get; set; } = 0;

		[Serialize, DisplayPriority(11)]
		[XmlAttribute("months_to_complete"), DisplayName("Months To Complete")]
		public float MonthsToComplete { get; set; } = 0.000000f;
	}
}
