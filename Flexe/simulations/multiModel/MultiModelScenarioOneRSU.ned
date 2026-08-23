import org.car2x.veins.nodes.RSU;
import org.car2x.veins.nodes.Scenario;

network MultiModelScenarioOneRSU extends Scenario{
    submodules:
        rsu[1]: RSU {
            @display("p=200,140;i=veins/sign/yellowdiamond;is=vs");
        }
}
