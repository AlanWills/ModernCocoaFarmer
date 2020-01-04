using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;

namespace MCF.Logic
{
    public enum ComparisonOperator
    {
        [Description("Less Than")]
        LessThan,

        [Description("Less Than Or Equal To")]
        LessThanOrEqualTo,

        [Description("Equals")]
        Equals,

        [Description("Greater Than Or Equal To")]
        GreaterThanOrEqualTo,

        [Description("Greater Than")]
        GreaterThan
    }
}
