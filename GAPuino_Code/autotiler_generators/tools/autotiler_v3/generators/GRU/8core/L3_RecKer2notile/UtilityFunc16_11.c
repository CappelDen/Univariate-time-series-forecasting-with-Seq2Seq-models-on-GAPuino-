#include "UtilityFunc16_11.h"



/**************************************************************************************************************************************
	Tangente iperbolica(ingresso(16,11)) risultato(16,11)
**************************************************************************************************************************************/
short int tan_h(short int x_value){
    short int i = x_value;
    short int r;
    _Bool inv=0;
    if (i>0){
	    i=-i;
	    inv=1;
    }
	if (i>=-2805) 
		if (i>=-1638) 
		    if (i>=-1064) 
		        if (i>=-778) 
		            if (i>=-634) 
		                if (i>=-552) 
		                    if (i>=-512) 
		                        if (i>=0) 
		                            r= 0;
		                        else 
		                            r= i;
		                    else 
		                        if (i>=-532) 
		                            r= -520;
		                        else 
		                            r= -539;
		                else 
		                    if (i>=-593) 
		                        if (i>=-573) 
		                            r= -558;
		                        else 
		                            r= -577;
		                    else 
		                        if (i>=-614) 
		                            r= -596;
		                        else 
		                            r= -615;
		            else 
		                if (i>=-716) 
		                    if (i>=-675) 
		                        if (i>=-655) 
		                            r= -633;
		                        else 
		                            r= -652;
		                    else 
		                        if (i>=-696) 
		                            r= -670;
		                        else 
		                            r= -688;
		                else 
		                    if (i>=-757) 
		                        if (i>=-737) 
		                            r= -706;
		                        else 
		                            r= -724;
		                    else 
		                        r= -742;
		        else 
		            if (i>=-921) 
		                if (i>=-860) 
		                    if (i>=-819) 
		                        if (i>=-798) 
		                            r= -760;
		                        else 
		                            r= -778;
		                    else 
		                        if (i>=-839) 
		                            r= -795;
		                        else 
		                            r= -812;
		                else 
		                    if (i>=-901) 
		                        if (i>=-880) 
		                            r= -830;
		                        else 
		                            r= -847;
		                    else 
		                        r= -864;
		            else 
		                if (i>=-1003) 
		                    if (i>=-962) 
		                        if (i>=-942) 
		                            r= -880;
		                        else 
		                            r= -897;
		                    else 
		                        if (i>=-983) 
		                            r= -913;
		                        else 
		                            r= -930;
		                else 
		                    if (i>=-1044) 
		                        if (i>=-1024) 
		                            r= -946;
		                        else 
		                            r= -962;
		                    else 
		                        r= -978;
		    else 
		        if (i>=-1351) 
		            if (i>=-1208) 
		                if (i>=-1146) 
		                    if (i>=-1105) 
		                        if (i>=-1085) 
		                            r= -994;
		                        else 
		                            r= -1009;
		                    else 
		                        if (i>=-1126) 
		                            r= -1025;
		                        else 
		                            r= -1040;
		                else 
		                    if (i>=-1187) 
		                        if (i>=-1167) 
		                            r= -1055;
		                        else 
		                            r= -1070;
		                    else 
		                        r= -1085;
		            else 
		                if (i>=-1290) 
		                    if (i>=-1249) 
		                        if (i>=-1228) 
		                            r= -1099;
		                        else 
		                            r= -1114;
		                    else 
		                        if (i>=-1269) 
		                            r= -1128;
		                        else 
		                            r= -1142;
		                else 
		                    if (i>=-1331) 
		                        if (i>=-1310) 
		                            r= -1156;
		                        else 
		                            r= -1170;
		                    else 
		                        r= -1184;
		        else 
		            if (i>=-1495) 
		                if (i>=-1433) 
		                    if (i>=-1392) 
		                        if (i>=-1372) 
		                            r= -1198;
		                        else 
		                            r= -1211;
		                    else 
		                        if (i>=-1413) 
		                            r= -1224;
		                        else 
		                            r= -1237;
		                else 
		                    if (i>=-1474) 
		                        if (i>=-1454) 
		                            r= -1250;
		                        else 
		                            r= -1263;
		                    else 
		                        r= -1276;
		            else 
		                if (i>=-1576) 
		                    if (i>=-1536) 
		                        if (i>=-1515) 
		                            r= -1288;
		                        else 
		                            r= -1300;
		                    else 
		                        if (i>=-1556) 
		                            r= -1312;
		                        else 
		                            r= -1324;
		                else 
		                    if (i>=-1617) 
		                        if (i>=-1597) 
		                            r= -1336;
		                        else 
		                            r= -1348;
		                    else 
		                        r= -1359;
		else 
		    if (i>=-2232) 
		        if (i>=-1945) 
		            if (i>=-1802) 
		                if (i>=-1720) 
		                    if (i>=-1679) 
		                        if (i>=-1658) 
		                            r= -1371;
		                        else 
		                            r= -1382;
		                    else 
		                        if (i>=-1699) 
		                            r= -1393;
		                        else 
		                            r= -1404;
		                else 
		                    if (i>=-1761) 
		                        if (i>=-1740) 
		                            r= -1415;
		                        else 
		                            r= -1425;
		                    else 
		                        if (i>=-1781) 
		                            r= -1436;
		                        else 
		                            r= -1446;
		            else 
		                if (i>=-1884) 
		                    if (i>=-1843) 
		                        if (i>=-1822) 
		                            r= -1456;
		                        else 
		                            r= -1466;
		                    else 
		                        if (i>=-1863) 
		                            r= -1476;
		                        else 
		                            r= -1486;
		                else 
		                    if (i>=-1925) 
		                        if (i>=-1904) 
		                            r= -1496;
		                        else 
		                            r= -1505;
		                    else 
		                        r= -1515;
		        else 
		            if (i>=-2088) 
		                if (i>=-2027) 
		                    if (i>=-1986) 
		                        if (i>=-1966) 
		                            r= -1524;
		                        else 
		                            r= -1533;
		                    else 
		                        if (i>=-2007) 
		                            r= -1542;
		                        else 
		                            r= -1551;
		                else 
		                    if (i>=-2068) 
		                        if (i>=-2048) 
		                            r= -1559;
		                        else 
		                            r= -1568;
		                    else 
		                        r= -1576;
		            else 
		                if (i>=-2170) 
		                    if (i>=-2129) 
		                        if (i>=-2109) 
		                            r= -1584;
		                        else 
		                            r= -1593;
		                    else 
		                        if (i>=-2150) 
		                            r= -1601;
		                        else 
		                            r= -1609;
		                else 
		                    if (i>=-2211) 
		                        if (i>=-2191) 
		                            r= -1616;
		                        else 
		                            r= -1624;
		                    else 
		                        r= -1632;
		    else 
		        if (i>=-2519) 
		            if (i>=-2375) 
		                if (i>=-2314) 
		                    if (i>=-2273) 
		                        if (i>=-2252) 
		                            r= -1639;
		                        else 
		                            r= -1646;
		                    else 
		                        if (i>=-2293) 
		                            r= -1653;
		                        else 
		                            r= -1660;
		                else 
		                    if (i>=-2355) 
		                        if (i>=-2334) 
		                            r= -1667;
		                        else 
		                            r= -1674;
		                    else 
		                        r= -1681;
		            else 
		                if (i>=-2457) 
		                    if (i>=-2416) 
		                        if (i>=-2396) 
		                            r= -1688;
		                        else 
		                            r= -1694;
		                    else 
		                        if (i>=-2437) 
		                            r= -1701;
		                        else 
		                            r= -1707;
		                else 
		                    if (i>=-2498) 
		                        if (i>=-2478) 
		                            r= -1713;
		                        else 
		                            r= -1719;
		                    else 
		                        r= -1725;
		        else 
		            if (i>=-2662) 
		                if (i>=-2600) 
		                    if (i>=-2560) 
		                        if (i>=-2539) 
		                            r= -1731;
		                        else 
		                            r= -1737;
		                    else 
		                        if (i>=-2580) 
		                            r= -1742;
		                        else 
		                            r= -1748;
		                else 
		                    if (i>=-2641) 
		                        if (i>=-2621) 
		                            r= -1754;
		                        else 
		                            r= -1759;
		                    else 
		                        r= -1764;
		            else 
		                if (i>=-2744) 
		                    if (i>=-2703) 
		                        if (i>=-2682) 
		                            r= -1770;
		                        else 
		                            r= -1775;
		                    else 
		                        if (i>=-2723) 
		                            r= -1780;
		                        else 
		                            r= -1785;
		                else 
		                    if (i>=-2785) 
		                        if (i>=-2764) 
		                            r= -1790;
		                        else 
		                            r= -1794;
		                    else 
		                        r= -1799;
	else 
		if (i>=-3973) 
		    if (i>=-3399) 
		        if (i>=-3112) 
		            if (i>=-2969) 
		                if (i>=-2887) 
		                    if (i>=-2846) 
		                        if (i>=-2826) 
		                            r= -1804;
		                        else 
		                            r= -1808;
		                    else 
		                        if (i>=-2867) 
		                            r= -1813;
		                        else 
		                            r= -1817;
		                else 
		                    if (i>=-2928) 
		                        if (i>=-2908) 
		                            r= -1821;
		                        else 
		                            r= -1826;
		                    else 
		                        if (i>=-2949) 
		                            r= -1830;
		                        else 
		                            r= -1834;
		            else 
		                if (i>=-3051) 
		                    if (i>=-3010) 
		                        if (i>=-2990) 
		                            r= -1838;
		                        else 
		                            r= -1842;
		                    else 
		                        if (i>=-3031) 
		                            r= -1846;
		                        else 
		                            r= -1850;
		                else 
		                    if (i>=-3092) 
		                        if (i>=-3072) 
		                            r= -1853;
		                        else 
		                            r= -1857;
		                    else 
		                        r= -1861;
		        else 
		            if (i>=-3256) 
		                if (i>=-3194) 
		                    if (i>=-3153) 
		                        if (i>=-3133) 
		                            r= -1864;
		                        else 
		                            r= -1868;
		                    else 
		                        if (i>=-3174) 
		                            r= -1871;
		                        else 
		                            r= -1874;
		                else 
		                    if (i>=-3235) 
		                        if (i>=-3215) 
		                            r= -1878;
		                        else 
		                            r= -1881;
		                    else 
		                        r= -1884;
		            else 
		                if (i>=-3338) 
		                    if (i>=-3297) 
		                        if (i>=-3276) 
		                            r= -1887;
		                        else 
		                            r= -1890;
		                    else 
		                        if (i>=-3317) 
		                            r= -1893;
		                        else 
		                            r= -1896;
		                else 
		                    if (i>=-3379) 
		                        if (i>=-3358) 
		                            r= -1899;
		                        else 
		                            r= -1902;
		                    else 
		                        r= -1905;
		    else 
		        if (i>=-3686) 
		            if (i>=-3543) 
		                if (i>=-3481) 
		                    if (i>=-3440) 
		                        if (i>=-3420) 
		                            r= -1907;
		                        else 
		                            r= -1910;
		                    else 
		                        if (i>=-3461) 
		                            r= -1913;
		                        else 
		                            r= -1915;
		                else 
		                    if (i>=-3522) 
		                        if (i>=-3502) 
		                            r= -1918;
		                        else 
		                            r= -1920;
		                    else 
		                        r= -1923;
		            else 
		                if (i>=-3624) 
		                    if (i>=-3584) 
		                        if (i>=-3563) 
		                            r= -1925;
		                        else 
		                            r= -1927;
		                    else 
		                        if (i>=-3604) 
		                            r= -1930;
		                        else 
		                            r= -1932;
		                else 
		                    if (i>=-3665) 
		                        if (i>=-3645) 
		                            r= -1934;
		                        else 
		                            r= -1936;
		                    else 
		                        r= -1939;
		        else 
		            if (i>=-3829) 
		                if (i>=-3768) 
		                    if (i>=-3727) 
		                        if (i>=-3706) 
		                            r= -1941;
		                        else 
		                            r= -1943;
		                    else 
		                        if (i>=-3747) 
		                            r= -1945;
		                        else 
		                            r= -1947;
		                else 
		                    if (i>=-3809) 
		                        if (i>=-3788) 
		                            r= -1949;
		                        else 
		                            r= -1951;
		                    else 
		                        r= -1952;
		            else 
		                if (i>=-3911) 
		                    if (i>=-3870) 
		                        if (i>=-3850) 
		                            r= -1954;
		                        else 
		                            r= -1956;
		                    else 
		                        if (i>=-3891) 
		                            r= -1958;
		                        else 
		                            r= -1960;
		                else 
		                    if (i>=-3952) 
		                        if (i>=-3932) 
		                            r= -1961;
		                        else 
		                            r= -1963;
		                    else 
		                        r= -1965;
		else 
		    if (i>=-4546) 
		        if (i>=-4259) 
		            if (i>=-4116) 
		                if (i>=-4055) 
		                    if (i>=-4014) 
		                        if (i>=-3993) 
		                            r= -1966;
		                        else 
		                            r= -1968;
		                    else 
		                        if (i>=-4034) 
		                            r= -1969;
		                        else 
		                            r= -1971;
		                else 
		                    if (i>=-4096) 
		                        if (i>=-4075) 
		                            r= -1972;
		                        else 
		                            r= -1974;
		                    else 
		                        r= -1975;
		            else 
		                if (i>=-4198) 
		                    if (i>=-4157) 
		                        if (i>=-4136) 
		                            r= -1977;
		                        else 
		                            r= -1978;
		                    else 
		                        if (i>=-4177) 
		                            r= -1979;
		                        else 
		                            r= -1981;
		                else 
		                    if (i>=-4239) 
		                        if (i>=-4218) 
		                            r= -1982;
		                        else 
		                            r= -1983;
		                    else 
		                        r= -1985;
		        else 
		            if (i>=-4403) 
		                if (i>=-4341) 
		                    if (i>=-4300) 
		                        if (i>=-4280) 
		                            r= -1986;
		                        else 
		                            r= -1987;
		                    else 
		                        if (i>=-4321) 
		                            r= -1988;
		                        else 
		                            r= -1989;
		                else 
		                    if (i>=-4382) 
		                        if (i>=-4362) 
		                            r= -1990;
		                        else 
		                            r= -1992;
		                    else 
		                        r= -1993;
		            else 
		                if (i>=-4485) 
		                    if (i>=-4444) 
		                        if (i>=-4423) 
		                            r= -1994;
		                        else 
		                            r= -1995;
		                    else 
		                        if (i>=-4464) 
		                            r= -1996;
		                        else 
		                            r= -1997;
		                else 
		                    if (i>=-4526) 
		                        if (i>=-4505) 
		                            r= -1998;
		                        else 
		                            r= -1999;
		                    else 
		                        r= -2000;
		    else 
		        if (i>=-4833) 
		            if (i>=-4689) 
		                if (i>=-4628) 
		                    if (i>=-4587) 
		                        if (i>=-4567) 
		                            r= -2001;
		                        else 
		                            r= -2002;
		                    else 
		                        if (i>=-4608) 
		                            r= -2002;
		                        else 
		                            r= -2003;
		                else 
		                    if (i>=-4669) 
		                        if (i>=-4648) 
		                            r= -2004;
		                        else 
		                            r= -2005;
		                    else 
		                        r= -2006;
		            else 
		                if (i>=-4771) 
		                    if (i>=-4730) 
		                        if (i>=-4710) 
		                            r= -2007;
		                        else 
		                            r= -2008;
		                    else 
		                        if (i>=-4751) 
		                            r= -2008;
		                        else 
		                            r= -2009;
		                else 
		                    if (i>=-4812) 
		                        if (i>=-4792) 
		                            r= -2010;
		                        else 
		                            r= -2011;
		                    else 
		                        r= -2011;
		        else 
		            if (i>=-4976) 
		                if (i>=-4915) 
		                    if (i>=-4874) 
		                        if (i>=-4853) 
		                            r= -2012;
		                        else 
		                            r= -2013;
		                    else 
		                        if (i>=-4894) 
		                            r= -2013;
		                        else 
		                            r= -2014;
		                else 
		                    if (i>=-4956) 
		                        if (i>=-4935) 
		                            r= -2015;
		                        else 
		                            r= -2015;
		                    else 
		                        r= -2016;
		            else 
		                if (i>=-5058) 
		                    if (i>=-5017) 
		                        if (i>=-4997) 
		                            r= -2017;
		                        else 
		                            r= -2017;
		                    else 
		                        if (i>=-5038) 
		                            r= -2018;
		                        else 
		                            r= -2018;
		                else 
		                    if (i>=-5099) 
		                        if (i>=-5079) 
		                            r= -2019;
		                        else 
		                            r= -2020;
		                    else 
		                        r= -2020;

    if (inv)
        return (-r);
    else 
        return r;

}

