using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace MCF.Time
{
	public class TimeManager : ScriptableObject
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("seconds_per_day"), DisplayName("Seconds Per Day")]
		public float SecondsPerDay { get; set; } = 0.050000f;
	}
}
