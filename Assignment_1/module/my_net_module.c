#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manavjeet Singh");
MODULE_DESCRIPTION("A netfilter hook module.");
MODULE_VERSION("1.0");

static struct nf_hook_ops *my_nf_hook = NULL;


static unsigned int hfunc(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
	// struct iphdr *iph;
	// struct udphdr *udph;
	// if (!skb)
	// 	return NF_ACCEPT;

	// iph = ip_hdr(skb);
	// if (iph->protocol == IPPROTO_UDP) {
	// 	udph = udp_hdr(skb);
	// 	if (ntohs(udph->dest) == 53) {
	// 		return NF_ACCEPT;
	// 	}
	// }
	// else if (iph->protocol == IPPROTO_TCP) {
	// 	return NF_ACCEPT;
	// }
	
	return NF_DROP;
}

static int __init my_net_module_init(void) {
	printk(KERN_INFO "Initializing my netfilter module\n");

	// Allocating memory for hook structure.
	my_nf_hook = (struct nf_hook_ops*) kzalloc(sizeof(struct nf_hook_ops), GFP_KERNEL);

	// Constructing the structure
	my_nf_hook->hook 	= (nf_hookfn*)hfunc;		/* hook function */
	my_nf_hook->hooknum 	= NF_INET_PRE_ROUTING;		/* received packets */
	my_nf_hook->pf 	= PF_INET;						/* IPv4 */
	my_nf_hook->priority 	= NF_IP_PRI_FIRST;			/* max hook priority */

	nf_register_net_hook(&init_net, my_nf_hook);
	return 0;
}

static void __exit my_net_module_exit(void) {

	nf_unregister_net_hook(&init_net, my_nf_hook);
	kfree(my_nf_hook);
	printk(KERN_INFO "Exiting my netfilter module\n");
}

module_init(my_net_module_init);
module_exit(my_net_module_exit);