#include "ns3/core-module.h"
#include "ns3/global-route-manager.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/bridge-module.h"
#include "ns3/csma-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main(int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

  /* Configuration. */

  /* Build nodes. */
  NodeContainer term_1;
  term_1.Create (1);
  NodeContainer term_2;
  term_2.Create (1);
  NodeContainer term_3;
  term_3.Create (1);
  NodeContainer router_0;
  router_0.Create (1);
  NodeContainer router_2;
  router_2.Create (1);
  NodeContainer term_4;
  term_4.Create (1);

  /* Build link. */
  CsmaHelper csma_hub_0;
  csma_hub_0.SetChannelAttribute ("DataRate", DataRateValue (100000000));
  csma_hub_0.SetChannelAttribute ("Delay", StringValue ("5ms"));
  CsmaHelper csma_hub_1;
  csma_hub_1.SetChannelAttribute ("DataRate", DataRateValue (100000000));
  csma_hub_1.SetChannelAttribute ("Delay", StringValue ("5ms"));
  CsmaHelper csma_hub_2;
  csma_hub_2.SetChannelAttribute ("DataRate", DataRateValue (100000000));
  csma_hub_2.SetChannelAttribute ("Delay", StringValue ("5ms"));
  CsmaHelper csma_hub_3;
  csma_hub_3.SetChannelAttribute ("DataRate", DataRateValue (100000000));
  csma_hub_3.SetChannelAttribute ("Delay", StringValue ("5ms"));
  CsmaHelper csma_hub_4;
  csma_hub_4.SetChannelAttribute ("DataRate", DataRateValue (100000000));
  csma_hub_4.SetChannelAttribute ("Delay", StringValue ("5ms"));

  /* Build link net device container. */
  NodeContainer all_hub_0;
  all_hub_0.Add (router_0);
  all_hub_0.Add (term_1);
  NetDeviceContainer ndc_hub_0 = csma_hub_0.Install (all_hub_0);
  NodeContainer all_hub_1;
  all_hub_1.Add (router_2);
  all_hub_1.Add (term_2);
  NetDeviceContainer ndc_hub_1 = csma_hub_1.Install (all_hub_1);
  NodeContainer all_hub_2;
  all_hub_2.Add (router_2);
  all_hub_2.Add (term_3);
  NetDeviceContainer ndc_hub_2 = csma_hub_2.Install (all_hub_2);
  NodeContainer all_hub_3;
  all_hub_3.Add (router_2);
  all_hub_3.Add (router_0);
  NetDeviceContainer ndc_hub_3 = csma_hub_3.Install (all_hub_3);
  NodeContainer all_hub_4;
  all_hub_4.Add (router_0);
  all_hub_4.Add (term_4);
  NetDeviceContainer ndc_hub_4 = csma_hub_4.Install (all_hub_4);

  /* Install the IP stack. */
  InternetStackHelper internetStackH;
  internetStackH.Install (term_1);
  internetStackH.Install (term_2);
  internetStackH.Install (term_3);
  internetStackH.Install (term_4);
  internetStackH.Install (router_0);
  internetStackH.Install (router_2);

  /* IP assign. */
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.0.0.0","255.255.255.0","0.0.0.1");
  Ipv4InterfaceContainer iface_ndc_hub_0 = ipv4.Assign (ndc_hub_0);
  
  ipv4.SetBase ("10.0.1.0","255.255.255.0","0.0.0.2");
  Ipv4InterfaceContainer iface_ndc_hub_1 = ipv4.Assign (ndc_hub_1);
  
  ipv4.SetBase ("10.0.2.0","255.255.255.0","0.0.0.3");
  Ipv4InterfaceContainer iface_ndc_hub_2 = ipv4.Assign (ndc_hub_2);
  
  ipv4.SetBase ("10.0.3.0","255.255.255.0","0.0.0.4");
  Ipv4InterfaceContainer iface_ndc_hub_3 = ipv4.Assign (ndc_hub_3);
  
  ipv4.SetBase ("10.0.4.0","255.255.255.0","0.0.0.5");
  Ipv4InterfaceContainer iface_ndc_hub_4 = ipv4.Assign (ndc_hub_4);

  /* Generate Route. */
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  /* Generate Application. */
  uint16_t port_tcp_0 = 1;
  Address sinkLocalAddress_tcp_0 (InetSocketAddress (Ipv4Address::GetAny (), port_tcp_0));
  PacketSinkHelper sinkHelper_tcp_0 ("ns3::TcpSocketFactory", sinkLocalAddress_tcp_0);
  ApplicationContainer sinkApp_tcp_0 = sinkHelper_tcp_0.Install (term_3);
  sinkApp_tcp_0.Start (Seconds (0.0));
  sinkApp_tcp_0.Stop (Seconds (1.0));
  OnOffHelper clientHelper_tcp_0 ("ns3::TcpSocketFactory", Address ());
  clientHelper_tcp_0.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
  clientHelper_tcp_0.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
  ApplicationContainer clientApps_tcp_0;
  AddressValue remoteAddress_tcp_0 (InetSocketAddress (iface_ndc_hub_2.GetAddress (1), port_tcp_0));
  clientHelper_tcp_0.SetAttribute ("Remote", remoteAddress_tcp_0);
  clientApps_tcp_0.Add (clientHelper_tcp_0.Install (term_4));
  clientApps_tcp_0.Start (Seconds (0.0));
  clientApps_tcp_0.Stop (Seconds (1.0));
  uint16_t port_tcp_1 = 3;
  Address sinkLocalAddress_tcp_1 (InetSocketAddress (Ipv4Address::GetAny (), port_tcp_1));
  PacketSinkHelper sinkHelper_tcp_1 ("ns3::TcpSocketFactory", sinkLocalAddress_tcp_1);
  ApplicationContainer sinkApp_tcp_1 = sinkHelper_tcp_1.Install (term_3);
  sinkApp_tcp_1.Start (Seconds (1.0));
  sinkApp_tcp_1.Stop (Seconds (2.0));
  OnOffHelper clientHelper_tcp_1 ("ns3::TcpSocketFactory", Address ());
  clientHelper_tcp_1.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
  clientHelper_tcp_1.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
  ApplicationContainer clientApps_tcp_1;
  AddressValue remoteAddress_tcp_1 (InetSocketAddress (iface_ndc_hub_2.GetAddress (1), port_tcp_1));
  clientHelper_tcp_1.SetAttribute ("Remote", remoteAddress_tcp_1);
  clientApps_tcp_1.Add (clientHelper_tcp_1.Install (term_4));
  clientApps_tcp_1.Start (Seconds (1.0));
  clientApps_tcp_1.Stop (Seconds (2.0));

  /* Simulation. */
  /* Pcap output. */
  /* Stop the simulation after x seconds. */
  uint32_t stopTime = 3;
  Simulator::Stop (Seconds (stopTime));
  /* Start and clean simulation. */
  AnimationInterface anim("anim1.xml");
  anim.SetConstantPosition(term_1.Get(0),1.0,2.0);
  anim.SetConstantPosition(term_4.Get(0),1.0,1.0);
  anim.SetConstantPosition(term_2.Get(0),2.0,2.0);
  anim.SetConstantPosition(term_3.Get(0),2.0,1.0);

  anim.SetConstantPosition(router_0.Get(0),1.3,1.5);
  anim.SetConstantPosition(router_2.Get(0),1.7,1.5);

  Simulator::Run ();
  Simulator::Destroy ();
}
