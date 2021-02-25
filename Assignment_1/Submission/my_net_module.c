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

static unsigned int hook_pre_route(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
	struct iphdr *iph;
	struct tcphdr *tcph;
	if (!skb)
		return NF_ACCEPT;

	iph = ip_hdr(skb);
	if (iph->protocol == IPPROTO_TCP) {
		tcph=tcp_hdr(skb);

		if (!tcph->syn && !tcph->rst && !tcph->psh && !tcph->ack && !tcph->urg && !tcph->ece && !tcph->cwr && !tcph->fin) {
			printk(KERN_INFO "TCP null scan packet detected\n");
			// return NF_DROP;
		}
		else if(!tcph->syn && !tcph->rst && tcph->psh && !tcph->ack && tcph->urg && !tcph->ece && !tcph->cwr && tcph->fin){
			printk(KERN_INFO "Xmas scan detected\n");
			// return NF_DROP;

		}
		else if(!tcph->syn && !tcph->rst && !tcph->psh && !tcph->ack && !tcph->urg && !tcph->ece && !tcph->cwr && tcph->fin){
			printk(KERN_INFO "Fin scan detected\n");
			// return NF_DROP;
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



	return 0;
}

static void __exit my_net_module_exit(void) {

	nf_unregister_net_hook(&init_net, my_nf_hook);
	kfree(my_nf_hook);
	printk(KERN_INFO "Exiting my netfilter module\n");
}

module_init(my_net_module_init);
module_exit(my_net_module_exit);