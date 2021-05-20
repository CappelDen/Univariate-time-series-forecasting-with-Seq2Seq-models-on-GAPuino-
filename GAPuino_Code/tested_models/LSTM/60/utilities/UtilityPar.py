import numpy as np

##Scaling Factors
scale_shift=11 
scale=pow(2,scale_shift)
unscale=pow(2, -scale_shift)
scale2=pow(2,scale_shift*2)
unscale2=pow(2,-scale_shift*2)

#16,13
scale_in=2
scale_out=2

def h_sig(i):
	inv = 0	
	p2_5 = np.int32(np.trunc(-2.5*scale))   #-2.5(32,12)
	Acc = np.int32(np.trunc(0.5*scale2))   #0.5(32,24)
	p0_2 = np.int32(np.trunc(0.2*scale))      #0.2(32,12)
	p1 = np.int32(np.trunc(1*scale2))   #1(32,24)	
	i = i>>scale_shift

	if (i>0):
		i = -i
		inv = 1
		
	if (i>=p2_5):
		r = Acc+p0_2*i #(32,24)		
	else:
		r = 0

	if (inv==1):
		r = (p1-r)>>scale_shift
		return r
	else:
		r = r>>scale_shift
		return r


def hard_sig(x, fun=h_sig):
    return np.vectorize(fun)(x) 
 

def tan_iper16(i):#valori di ingresso e uscita espressi inizialmente come 16,13
	i=i>>scale_shift
	inv=0
	if i>0:
		i=-i 
		inv=1

	if i>= (-11223>>scale_in) :
		if i>= (-6553>>scale_in) :
		    if i>= (-4259>>scale_in) :
		        if i>= (-3112>>scale_in) :
		            if i>= (-2539>>scale_in) :
		                if i>= (-2211>>scale_in) :
		                    if i>= (-2048>>scale_in) :
		                        if i>= (0>>scale_in) :
		                            r= (0>>scale_out)
		                        else :
		                            r= (i)
		                    else :
		                        if i>= (-2129>>scale_in) :
		                            r= (-2083>>scale_out)
		                        else :
		                            r= (-2159>>scale_out)
		                else :
		                    if i>= (-2375>>scale_in) :
		                        if i>= (-2293>>scale_in) :
		                            r= (-2235>>scale_out)
		                        else :
		                            r= (-2311>>scale_out)
		                    else :
		                        if i>= (-2457>>scale_in) :
		                            r= (-2386>>scale_out)
		                        else :
		                            r= (-2461>>scale_out)
		            else :
		                if i>= (-2867>>scale_in) :
		                    if i>= (-2703>>scale_in) :
		                        if i>= (-2621>>scale_in) :
		                            r= (-2535>>scale_out)
		                        else :
		                            r= (-2609>>scale_out)
		                    else :
		                        if i>= (-2785>>scale_in) :
		                            r= (-2682>>scale_out)
		                        else :
		                            r= (-2755>>scale_out)
		                else :
		                    if i>= (-3031>>scale_in) :
		                        if i>= (-2949>>scale_in) :
		                            r= (-2827>>scale_out)
		                        else :
		                            r= (-2899>>scale_out)
		                    else :
		                        r= (-2971>>scale_out)
		        else :
		            if i>= (-3686>>scale_in) :
		                if i>= (-3440>>scale_in) :
		                    if i>= (-3276>>scale_in) :
		                        if i>= (-3194>>scale_in) :
		                            r= (-3042>>scale_out)
		                        else :
		                            r= (-3112>>scale_out)
		                    else :
		                        if i>= (-3358>>scale_in) :
		                            r= (-3182>>scale_out)
		                        else :
		                            r= (-3251>>scale_out)
		                else :
		                    if i>= (-3604>>scale_in) :
		                        if i>= (-3522>>scale_in) :
		                            r= (-3320>>scale_out)
		                        else :
		                            r= (-3388>>scale_out)
		                    else :
		                        r= (-3456>>scale_out)
		            else :
		                if i>= (-4014>>scale_in) :
		                    if i>= (-3850>>scale_in) :
		                        if i>= (-3768>>scale_in) :
		                            r= (-3523>>scale_out)
		                        else :
		                            r= (-3589>>scale_out)
		                    else :
		                        if i>= (-3932>>scale_in) :
		                            r= (-3655>>scale_out)
		                        else :
		                            r= (-3720>>scale_out)
		                else :
		                    if i>= (-4177>>scale_in) :
		                        if i>= (-4096>>scale_in) :
		                            r= (-3785>>scale_out)
		                        else :
		                            r= (-3849>>scale_out)
		                    else :
		                        r= (-3913>>scale_out)
		    else :
		        if i>= (-5406>>scale_in) :
		            if i>= (-4833>>scale_in) :
		                if i>= (-4587>>scale_in) :
		                    if i>= (-4423>>scale_in) :
		                        if i>= (-4341>>scale_in) :
		                            r= (-3976>>scale_out)
		                        else :
		                            r= (-4038>>scale_out)
		                    else :
		                        if i>= (-4505>>scale_in) :
		                            r= (-4100>>scale_out)
		                        else :
		                            r= (-4161>>scale_out)
		                else :
		                    if i>= (-4751>>scale_in) :
		                        if i>= (-4669>>scale_in) :
		                            r= (-4221>>scale_out)
		                        else :
		                            r= (-4281>>scale_out)
		                    else :
		                        r= (-4340>>scale_out)
		            else :
		                if i>= (-5160>>scale_in) :
		                    if i>= (-4997>>scale_in) :
		                        if i>= (-4915>>scale_in) :
		                            r= (-4399>>scale_out)
		                        else :
		                            r= (-4457>>scale_out)
		                    else :
		                        if i>= (-5079>>scale_in) :
		                            r= (-4514>>scale_out)
		                        else :
		                            r= (-4571>>scale_out)
		                else :
		                    if i>= (-5324>>scale_in) :
		                        if i>= (-5242>>scale_in) :
		                            r= (-4627>>scale_out)
		                        else :
		                            r= (-4683>>scale_out)
		                    else :
		                        r= (-4737>>scale_out)
		        else :
		            if i>= (-5980>>scale_in) :
		                if i>= (-5734>>scale_in) :
		                    if i>= (-5570>>scale_in) :
		                        if i>= (-5488>>scale_in) :
		                            r= (-4792>>scale_out)
		                        else :
		                            r= (-4845>>scale_out)
		                    else :
		                        if i>= (-5652>>scale_in) :
		                            r= (-4898>>scale_out)
		                        else :
		                            r= (-4950>>scale_out)
		                else :
		                    if i>= (-5898>>scale_in) :
		                        if i>= (-5816>>scale_in) :
		                            r= (-5002>>scale_out)
		                        else :
		                            r= (-5053>>scale_out)
		                    else :
		                        r= (-5104>>scale_out)
		            else :
		                if i>= (-6307>>scale_in) :
		                    if i>= (-6144>>scale_in) :
		                        if i>= (-6062>>scale_in) :
		                            r= (-5153>>scale_out)
		                        else :
		                            r= (-5203>>scale_out)
		                    else :
		                        if i>= (-6225>>scale_in) :
		                            r= (-5251>>scale_out)
		                        else :
		                            r= (-5299>>scale_out)
		                else :
		                    if i>= (-6471>>scale_in) :
		                        if i>= (-6389>>scale_in) :
		                            r= (-5346>>scale_out)
		                        else :
		                            r= (-5393>>scale_out)
		                    else :
		                        r= (-5439>>scale_out)
		else :
		    if i>= (-8929>>scale_in) :
		        if i>= (-7782>>scale_in) :
		            if i>= (-7208>>scale_in) :
		                if i>= (-6881>>scale_in) :
		                    if i>= (-6717>>scale_in) :
		                        if i>= (-6635>>scale_in) :
		                            r= (-5485>>scale_out)
		                        else :
		                            r= (-5530>>scale_out)
		                    else :
		                        if i>= (-6799>>scale_in) :
		                            r= (-5574>>scale_out)
		                        else :
		                            r= (-5618>>scale_out)
		                else :
		                    if i>= (-7045>>scale_in) :
		                        if i>= (-6963>>scale_in) :
		                            r= (-5661>>scale_out)
		                        else :
		                            r= (-5703>>scale_out)
		                    else :
		                        if i>= (-7127>>scale_in) :
		                            r= (-5745>>scale_out)
		                        else :
		                            r= (-5786>>scale_out)
		            else :
		                if i>= (-7536>>scale_in) :
		                    if i>= (-7372>>scale_in) :
		                        if i>= (-7290>>scale_in) :
		                            r= (-5827>>scale_out)
		                        else :
		                            r= (-5867>>scale_out)
		                    else :
		                        if i>= (-7454>>scale_in) :
		                            r= (-5907>>scale_out)
		                        else :
		                            r= (-5946>>scale_out)
		                else :
		                    if i>= (-7700>>scale_in) :
		                        if i>= (-7618>>scale_in) :
		                            r= (-5985>>scale_out)
		                        else :
		                            r= (-6022>>scale_out)
		                    else :
		                        r= (-6060>>scale_out)
		        else :
		            if i>= (-8355>>scale_in) :
		                if i>= (-8110>>scale_in) :
		                    if i>= (-7946>>scale_in) :
		                        if i>= (-7864>>scale_in) :
		                            r= (-6097>>scale_out)
		                        else :
		                            r= (-6133>>scale_out)
		                    else :
		                        if i>= (-8028>>scale_in) :
		                            r= (-6169>>scale_out)
		                        else :
		                            r= (-6204>>scale_out)
		                else :
		                    if i>= (-8273>>scale_in) :
		                        if i>= (-8192>>scale_in) :
		                            r= (-6238>>scale_out)
		                        else :
		                            r= (-6273>>scale_out)
		                    else :
		                        r= (-6306>>scale_out)
		            else :
		                if i>= (-8683>>scale_in) :
		                    if i>= (-8519>>scale_in) :
		                        if i>= (-8437>>scale_in) :
		                            r= (-6339>>scale_out)
		                        else :
		                            r= (-6372>>scale_out)
		                    else :
		                        if i>= (-8601>>scale_in) :
		                            r= (-6404>>scale_out)
		                        else :
		                            r= (-6436>>scale_out)
		                else :
		                    if i>= (-8847>>scale_in) :
		                        if i>= (-8765>>scale_in) :
		                            r= (-6467>>scale_out)
		                        else :
		                            r= (-6497>>scale_out)
		                    else :
		                        r= (-6528>>scale_out)
		    else :
		        if i>= (-10076>>scale_in) :
		            if i>= (-9502>>scale_in) :
		                if i>= (-9256>>scale_in) :
		                    if i>= (-9093>>scale_in) :
		                        if i>= (-9011>>scale_in) :
		                            r= (-6557>>scale_out)
		                        else :
		                            r= (-6586>>scale_out)
		                    else :
		                        if i>= (-9175>>scale_in) :
		                            r= (-6615>>scale_out)
		                        else :
		                            r= (-6643>>scale_out)
		                else :
		                    if i>= (-9420>>scale_in) :
		                        if i>= (-9338>>scale_in) :
		                            r= (-6671>>scale_out)
		                        else :
		                            r= (-6699>>scale_out)
		                    else :
		                        r= (-6725>>scale_out)
		            else :
		                if i>= (-9830>>scale_in) :
		                    if i>= (-9666>>scale_in) :
		                        if i>= (-9584>>scale_in) :
		                            r= (-6752>>scale_out)
		                        else :
		                            r= (-6778>>scale_out)
		                    else :
		                        if i>= (-9748>>scale_in) :
		                            r= (-6804>>scale_out)
		                        else :
		                            r= (-6829>>scale_out)
		                else :
		                    if i>= (-9994>>scale_in) :
		                        if i>= (-9912>>scale_in) :
		                            r= (-6854>>scale_out)
		                        else :
		                            r= (-6878>>scale_out)
		                    else :
		                        r= (-6902>>scale_out)
		        else :
		            if i>= (-10649>>scale_in) :
		                if i>= (-10403>>scale_in) :
		                    if i>= (-10240>>scale_in) :
		                        if i>= (-10158>>scale_in) :
		                            r= (-6925>>scale_out)
		                        else :
		                            r= (-6949>>scale_out)
		                    else :
		                        if i>= (-10321>>scale_in) :
		                            r= (-6971>>scale_out)
		                        else :
		                            r= (-6994>>scale_out)
		                else :
		                    if i>= (-10567>>scale_in) :
		                        if i>= (-10485>>scale_in) :
		                            r= (-7016>>scale_out)
		                        else :
		                            r= (-7037>>scale_out)
		                    else :
		                        r= (-7059>>scale_out)
		            else :
		                if i>= (-10977>>scale_in) :
		                    if i>= (-10813>>scale_in) :
		                        if i>= (-10731>>scale_in) :
		                            r= (-7080>>scale_out)
		                        else :
		                            r= (-7100>>scale_out)
		                    else :
		                        if i>= (-10895>>scale_in) :
		                            r= (-7120>>scale_out)
		                        else :
		                            r= (-7140>>scale_out)
		                else :
		                    if i>= (-11141>>scale_in) :
		                        if i>= (-11059>>scale_in) :
		                            r= (-7160>>scale_out)
		                        else :
		                            r= (-7179>>scale_out)
		                    else :
		                        r= (-7198>>scale_out)
	else :
		if i>= (-15892>>scale_in) :
		    if i>= (-13598>>scale_in) :
		        if i>= (-12451>>scale_in) :
		            if i>= (-11878>>scale_in) :
		                if i>= (-11550>>scale_in) :
		                    if i>= (-11386>>scale_in) :
		                        if i>= (-11304>>scale_in) :
		                            r= (-7216>>scale_out)
		                        else :
		                            r= (-7234>>scale_out)
		                    else :
		                        if i>= (-11468>>scale_in) :
		                            r= (-7252>>scale_out)
		                        else :
		                            r= (-7270>>scale_out)
		                else :
		                    if i>= (-11714>>scale_in) :
		                        if i>= (-11632>>scale_in) :
		                            r= (-7287>>scale_out)
		                        else :
		                            r= (-7304>>scale_out)
		                    else :
		                        if i>= (-11796>>scale_in) :
		                            r= (-7321>>scale_out)
		                        else :
		                            r= (-7337>>scale_out)
		            else :
		                if i>= (-12206>>scale_in) :
		                    if i>= (-12042>>scale_in) :
		                        if i>= (-11960>>scale_in) :
		                            r= (-7353>>scale_out)
		                        else :
		                            r= (-7369>>scale_out)
		                    else :
		                        if i>= (-12124>>scale_in) :
		                            r= (-7384>>scale_out)
		                        else :
		                            r= (-7400>>scale_out)
		                else :
		                    if i>= (-12369>>scale_in) :
		                        if i>= (-12288>>scale_in) :
		                            r= (-7414>>scale_out)
		                        else :
		                            r= (-7429>>scale_out)
		                    else :
		                        r= (-7444>>scale_out)
		        else :
		            if i>= (-13025>>scale_in) :
		                if i>= (-12779>>scale_in) :
		                    if i>= (-12615>>scale_in) :
		                        if i>= (-12533>>scale_in) :
		                            r= (-7458>>scale_out)
		                        else :
		                            r= (-7472>>scale_out)
		                    else :
		                        if i>= (-12697>>scale_in) :
		                            r= (-7485>>scale_out)
		                        else :
		                            r= (-7499>>scale_out)
		                else :
		                    if i>= (-12943>>scale_in) :
		                        if i>= (-12861>>scale_in) :
		                            r= (-7512>>scale_out)
		                        else :
		                            r= (-7525>>scale_out)
		                    else :
		                        r= (-7537>>scale_out)
		            else :
		                if i>= (-13352>>scale_in) :
		                    if i>= (-13189>>scale_in) :
		                        if i>= (-13107>>scale_in) :
		                            r= (-7550>>scale_out)
		                        else :
		                            r= (-7562>>scale_out)
		                    else :
		                        if i>= (-13271>>scale_in) :
		                            r= (-7574>>scale_out)
		                        else :
		                            r= (-7586>>scale_out)
		                else :
		                    if i>= (-13516>>scale_in) :
		                        if i>= (-13434>>scale_in) :
		                            r= (-7597>>scale_out)
		                        else :
		                            r= (-7609>>scale_out)
		                    else :
		                        r= (-7620>>scale_out)
		    else :
		        if i>= (-14745>>scale_in) :
		            if i>= (-14172>>scale_in) :
		                if i>= (-13926>>scale_in) :
		                    if i>= (-13762>>scale_in) :
		                        if i>= (-13680>>scale_in) :
		                            r= (-7631>>scale_out)
		                        else :
		                            r= (-7642>>scale_out)
		                    else :
		                        if i>= (-13844>>scale_in) :
		                            r= (-7652>>scale_out)
		                        else :
		                            r= (-7662>>scale_out)
		                else :
		                    if i>= (-14090>>scale_in) :
		                        if i>= (-14008>>scale_in) :
		                            r= (-7673>>scale_out)
		                        else :
		                            r= (-7682>>scale_out)
		                    else :
		                        r= (-7692>>scale_out)
		            else :
		                if i>= (-14499>>scale_in) :
		                    if i>= (-14336>>scale_in) :
		                        if i>= (-14254>>scale_in) :
		                            r= (-7702>>scale_out)
		                        else :
		                            r= (-7711>>scale_out)
		                    else :
		                        if i>= (-14417>>scale_in) :
		                            r= (-7720>>scale_out)
		                        else :
		                            r= (-7730>>scale_out)
		                else :
		                    if i>= (-14663>>scale_in) :
		                        if i>= (-14581>>scale_in) :
		                            r= (-7738>>scale_out)
		                        else :
		                            r= (-7747>>scale_out)
		                    else :
		                        r= (-7756>>scale_out)
		        else :
		            if i>= (-15319>>scale_in) :
		                if i>= (-15073>>scale_in) :
		                    if i>= (-14909>>scale_in) :
		                        if i>= (-14827>>scale_in) :
		                            r= (-7764>>scale_out)
		                        else :
		                            r= (-7772>>scale_out)
		                    else :
		                        if i>= (-14991>>scale_in) :
		                            r= (-7780>>scale_out)
		                        else :
		                            r= (-7788>>scale_out)
		                else :
		                    if i>= (-15237>>scale_in) :
		                        if i>= (-15155>>scale_in) :
		                            r= (-7796>>scale_out)
		                        else :
		                            r= (-7804>>scale_out)
		                    else :
		                        r= (-7811>>scale_out)
		            else :
		                if i>= (-15646>>scale_in) :
		                    if i>= (-15482>>scale_in) :
		                        if i>= (-15400>>scale_in) :
		                            r= (-7819>>scale_out)
		                        else :
		                            r= (-7826>>scale_out)
		                    else :
		                        if i>= (-15564>>scale_in) :
		                            r= (-7833>>scale_out)
		                        else :
		                            r= (-7840>>scale_out)
		                else :
		                    if i>= (-15810>>scale_in) :
		                        if i>= (-15728>>scale_in) :
		                            r= (-7847>>scale_out)
		                        else :
		                            r= (-7853>>scale_out)
		                    else :
		                        r= (-7860>>scale_out)
		else :
		    if i>= (-18186>>scale_in) :
		        if i>= (-17039>>scale_in) :
		            if i>= (-16465>>scale_in) :
		                if i>= (-16220>>scale_in) :
		                    if i>= (-16056>>scale_in) :
		                        if i>= (-15974>>scale_in) :
		                            r= (-7866>>scale_out)
		                        else :
		                            r= (-7873>>scale_out)
		                    else :
		                        if i>= (-16138>>scale_in) :
		                            r= (-7879>>scale_out)
		                        else :
		                            r= (-7885>>scale_out)
		                else :
		                    if i>= (-16384>>scale_in) :
		                        if i>= (-16302>>scale_in) :
		                            r= (-7891>>scale_out)
		                        else :
		                            r= (-7897>>scale_out)
		                    else :
		                        r= (-7903>>scale_out)
		            else :
		                if i>= (-16793>>scale_in) :
		                    if i>= (-16629>>scale_in) :
		                        if i>= (-16547>>scale_in) :
		                            r= (-7908>>scale_out)
		                        else :
		                            r= (-7914>>scale_out)
		                    else :
		                        if i>= (-16711>>scale_in) :
		                            r= (-7919>>scale_out)
		                        else :
		                            r= (-7924>>scale_out)
		                else :
		                    if i>= (-16957>>scale_in) :
		                        if i>= (-16875>>scale_in) :
		                            r= (-7930>>scale_out)
		                        else :
		                            r= (-7935>>scale_out)
		                    else :
		                        r= (-7940>>scale_out)
		        else :
		            if i>= (-17612>>scale_in) :
		                if i>= (-17367>>scale_in) :
		                    if i>= (-17203>>scale_in) :
		                        if i>= (-17121>>scale_in) :
		                            r= (-7945>>scale_out)
		                        else :
		                            r= (-7949>>scale_out)
		                    else :
		                        if i>= (-17285>>scale_in) :
		                            r= (-7954>>scale_out)
		                        else :
		                            r= (-7959>>scale_out)
		                else :
		                    if i>= (-17530>>scale_in) :
		                        if i>= (-17448>>scale_in) :
		                            r= (-7963>>scale_out)
		                        else :
		                            r= (-7968>>scale_out)
		                    else :
		                        r= (-7972>>scale_out)
		            else :
		                if i>= (-17940>>scale_in) :
		                    if i>= (-17776>>scale_in) :
		                        if i>= (-17694>>scale_in) :
		                            r= (-7976>>scale_out)
		                        else :
		                            r= (-7981>>scale_out)
		                    else :
		                        if i>= (-17858>>scale_in) :
		                            r= (-7985>>scale_out)
		                        else :
		                            r= (-7989>>scale_out)
		                else :
		                    if i>= (-18104>>scale_in) :
		                        if i>= (-18022>>scale_in) :
		                            r= (-7993>>scale_out)
		                        else :
		                            r= (-7997>>scale_out)
		                    else :
		                        r= (-8000>>scale_out)
		    else :
		        if i>= (-19333>>scale_in) :
		            if i>= (-18759>>scale_in) :
		                if i>= (-18513>>scale_in) :
		                    if i>= (-18350>>scale_in) :
		                        if i>= (-18268>>scale_in) :
		                            r= (-8004>>scale_out)
		                        else :
		                            r= (-8008>>scale_out)
		                    else :
		                        if i>= (-18432>>scale_in) :
		                            r= (-8011>>scale_out)
		                        else :
		                            r= (-8015>>scale_out)
		                else :
		                    if i>= (-18677>>scale_in) :
		                        if i>= (-18595>>scale_in) :
		                            r= (-8018>>scale_out)
		                        else :
		                            r= (-8022>>scale_out)
		                    else :
		                        r= (-8025>>scale_out)
		            else :
		                if i>= (-19087>>scale_in) :
		                    if i>= (-18923>>scale_in) :
		                        if i>= (-18841>>scale_in) :
		                            r= (-8028>>scale_out)
		                        else :
		                            r= (-8032>>scale_out)
		                    else :
		                        if i>= (-19005>>scale_in) :
		                            r= (-8035>>scale_out)
		                        else :
		                            r= (-8038>>scale_out)
		                else :
		                    if i>= (-19251>>scale_in) :
		                        if i>= (-19169>>scale_in) :
		                            r= (-8041>>scale_out)
		                        else :
		                            r= (-8044>>scale_out)
		                    else :
		                        r= (-8047>>scale_out)
		        else :
		            if i>= (-19906>>scale_in) :
		                if i>= (-19660>>scale_in) :
		                    if i>= (-19496>>scale_in) :
		                        if i>= (-19415>>scale_in) :
		                            r= (-8050>>scale_out)
		                        else :
		                            r= (-8052>>scale_out)
		                    else :
		                        if i>= (-19578>>scale_in) :
		                            r= (-8055>>scale_out)
		                        else :
		                            r= (-8058>>scale_out)
		                else :
		                    if i>= (-19824>>scale_in) :
		                        if i>= (-19742>>scale_in) :
		                            r= (-8060>>scale_out)
		                        else :
		                            r= (-8063>>scale_out)
		                    else :
		                        r= (-8065>>scale_out)
		            else :
		                if i>= (-20234>>scale_in) :
		                    if i>= (-20070>>scale_in) :
		                        if i>= (-19988>>scale_in) :
		                            r= (-8068>>scale_out)
		                        else :
		                            r= (-8070>>scale_out)
		                    else :
		                        if i>= (-20152>>scale_in) :
		                            r= (-8073>>scale_out)
		                        else :
		                            r= (-8075>>scale_out)
		                else :
		                    if i>= (-20398>>scale_in) :
		                        if i>= (-20316>>scale_in) :
		                            r= (-8077>>scale_out)
		                        else :
		                            r= (-8080>>scale_out)
		                    else :
		                        r= (-8082>>scale_out)

	if inv==1:
		return -r
	else: 
		return r    


def tanh(x,fun= tan_iper16):
    return np.vectorize(fun)(x)

    
