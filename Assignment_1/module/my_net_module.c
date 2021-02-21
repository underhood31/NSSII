#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <net/netfilter/nf_conntrack.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manavjeet Singh");
MODULE_DESCRIPTION("A netfilter hook module.");
MODULE_VERSION("1.0");

static struct nf_hook_ops *my_nf_hook = NULL;
static struct nf_hook_ops *my_nf_conntrack_hook = NULL;
// static unsigned int hfunc(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
// 	struct iphdr *iph;
// 	struct udphdr *udph;
// 	if (!skb)
// 		return NF_ACCEPT;

// 	iph = ip_hdr(skb);
// 	if (iph->protocol == IPPROTO_UDP) {
// 		udph = udp_hdr(skb);
// 		if (ntohs(udph->dest) == 53) {
// 			return NF_ACCEPT;
// 		}
// 	}
// 	else if (iph->protocol == IPPROTO_TCP) {
// 		return NF_ACCEPT;
// 	}
	
// 	return NF_DROP;
// }

static unsigned int hook_pre_route(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
	struct iphdr *iph;
	struct tcphdr *tcph;
	unsigned int option_length;
	if (!skb)
		return NF_ACCEPT;

	iph = ip_hdr(skb);
	if (iph->protocol == IPPROTO_TCP) {
		tcph=tcp_hdr(skb);

		if (!tcph->syn && !tcph->rst && !tcph->psh && !tcph->ack && !tcph->urg && !tcph->ece && !tcph->cwr && !tcph->fin) {
			printk(KERN_INFO "TCP null scan packet detected\n");
			return NF_DROP;
		}
		else if (tcph->syn) {

			option_length=tcp_optlen(skb);
			if(option_length==4) {
				printk(KERN_INFO "nmap half open TCP SYN packet found");
				return NF_DROP;
			}
		}

	}

	
	return NF_ACCEPT;
}

static unsigned int hook_conntrack (void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
	struct iphdr *iph;
	struct tcphdr *tcph;
	struct nf_conn *ct;
	enum ip_conntrack_info conn_info;

	iph=ip_hdr(skb);
	if (iph->protocol == IPPROTO_TCP) {
		ct=nf_ct_get(skb,&conn_info);

		tcph=tcp_hdr(skb);

		if (conn_info == IP_CT_ESTABLISHED ){
			printk(KERN_INFO "IP_CT_ESTABLISHED\n");
		}
		else if (conn_info == IP_CT_RELATED ){
			printk(KERN_INFO "IP_CT_RELATED\n");
		}
		else if (conn_info == IP_CT_NEW ){
			printk(KERN_INFO "IP_CT_NEW\n");
		}
		else if (conn_info == IP_CT_IS_REPLY ){
			printk(KERN_INFO "IP_CT_IS_REPLY\n");
		}
		else if (conn_info == IP_CT_ESTABLISHED_REPLY ){
			printk(KERN_INFO "IP_CT_ESTABLISHED_REPLY\n");
		}
		else if (conn_info == IP_CT_RELATED_REPLY ){
			printk(KERN_INFO "IP_CT_RELATED_REPLY\n");
		}
		else if (conn_info == IP_CT_NEW_REPLY ){
			printk(KERN_INFO "IP_CT_NEW_REPLY\n");
		}
		else if (conn_info == IP_CT_NUMBER ){
			printk(KERN_INFO "IP_CT_NUMBER\n");
		}
		else{
			printk(KERN_INFO "NONE\n");
		}
	}
	return NF_ACCEPT;
}

static int __init my_net_module_init(void) {
	printk(KERN_INFO "Initializing my netfilter module\n");

	/*Hook for which connection tracking is not required*/
	my_nf_hook = (struct nf_hook_ops*) kzalloc(sizeof(struct nf_hook_ops), GFP_KERNEL);

	my_nf_hook->hook 			= (nf_hookfn*)hook_pre_route;	/* hook function */
	my_nf_hook->hooknum 		= NF_INET_PRE_ROUTING;			/* received packets */
	my_nf_hook->pf 				= PF_INET;						/* IPv4 */
	my_nf_hook->priority 		= NF_IP_PRI_FIRST;				/* max hook priority */

	nf_register_net_hook(&init_net, my_nf_hook);

	/*Hook which requires connection tracking using conntrack*/
	my_nf_conntrack_hook = (struct nf_hook_ops*) kzalloc(sizeof(struct nf_hook_ops), GFP_KERNEL);

	my_nf_conntrack_hook->hook 		= (nf_hookfn*)hook_conntrack;	/* hook function */
	my_nf_conntrack_hook->hooknum 	= NF_INET_PRE_ROUTING;			/* received packets */
	my_nf_conntrack_hook->pf 		= PF_INET;						/* IPv4 */
	my_nf_conntrack_hook->priority 	= NF_IP_PRI_CONNTRACK + 150;	/* priority less than conntrack */

	nf_register_net_hook(&init_net, my_nf_conntrack_hook);

	return 0;
}

static void __exit my_net_module_exit(void) {

	nf_unregister_net_hook(&init_net, my_nf_hook);
	nf_unregister_net_hook(&init_net, my_nf_conntrack_hook);
	kfree(my_nf_hook);
	kfree(my_nf_conntrack_hook);
	printk(KERN_INFO "Exiting my netfilter module\n");
}

module_init(my_net_module_init);
module_exit(my_net_module_exit);