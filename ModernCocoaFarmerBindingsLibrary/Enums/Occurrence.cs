using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;

namespace MCF.Stats
{
    public enum Occurrence
    {
        [Description("Instant")]
        Instant,

        [Description("Periodic")]
        Periodic
    }
}
