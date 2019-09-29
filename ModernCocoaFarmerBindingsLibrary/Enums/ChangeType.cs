using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;

namespace MCF.Stats
{
    public enum ChangeType
    {
        [Description("Delta")]
        Delta,

        [Description("Absolute")]
        Absolute
    }
}
