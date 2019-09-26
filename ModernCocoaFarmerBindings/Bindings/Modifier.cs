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
	public class Modifier : ScriptableObject
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("amount"), DisplayName("Amount")]
		public int Amount { get; set; } = 0;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("change_type"), DisplayName("Change Type")]
		public ChangeType ChangeType { get; set; } = ChangeType.Delta;

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("occurrence"), DisplayName("Occurrence")]
		public Occurrence Occurrence { get; set; } = Occurrence.Instant;

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("monthly_frequency"), DisplayName("Monthly Frequency")]
		public float MonthlyFrequency { get; set; } = 0.000000f;
	}
}
