using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace MCF.Money
{
	public class MoneyManager : ScriptableObject
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("money"), DisplayName("Money")]
		public int Money { get; set; } = 100;
	}
}
