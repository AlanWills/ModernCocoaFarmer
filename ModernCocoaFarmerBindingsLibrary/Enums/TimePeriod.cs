using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;

namespace MCF.Time
{
    public enum TimePeriod
    {
        [Description("Day")]
        Day,

        [Description("Month")]
        Month,

        [Description("Year")]
        Year
    }
}
