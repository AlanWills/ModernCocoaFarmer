using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace MCF.Events.Conditions
{
	public class TimeComparisonCondition : ScriptableObject
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("time_period"), DisplayName("Time Period")]
		public Time.TimePeriod TimePeriod { get; set; }

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("comparison_operator"), DisplayName("Comparison Operator")]
		public Logic.ComparisonOperator ComparisonOperator { get; set; }

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("value"), DisplayName("Value")]
		public int Value { get; set; } = 0;
	}
}
