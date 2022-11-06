#include "repository.h"
#include "../CustomException/customException.h"

#include <iostream>
#include <fstream>
#include <algorithm>

void Repository::addDogRepo(const Dog &el) {
	/*
		Adds a dog to the repository

	 	el - Dog to be added to the repository
	*/

	if (checkDogExiNameBreedRepoAdd(el.getBreed(), el.getName())) {
		throw CustomException("Dog already exists!");
	}

	this->dyn_arr.push_back(el);
	this->writeFile();
}

void Repository::deleteDogRepo(int idx) {
	/*
		Deletes a dog to the repository

	 	idx - Index of dog to be deleted
	*/

	if (!checkDogExiNameBreedRepoDelUpd(idx)) {
		throw CustomException("Dog doesn't exist!");
	}
	if (!this->dyn_arr[idx].getIsAdopted()) {
		throw CustomException("You can only delete adopted dogs from the database!");
	}

	this->dyn_arr.erase(this->dyn_arr.begin() + idx);
	this->writeFile();
}

void Repository::updateDogRepo(const Dog &el, int idx) {
	/*
		Updates a dog in the repository

	 	el - New element with new values to be replaced
	 	idx - Index of dog to be updated
	*/

	if (!checkDogExiNameBreedRepoDelUpd(idx)) {
		throw CustomException("Dog doesn't exist!");
	}

	this->dyn_arr[idx] = el;
	this->writeFile();
}

std::vector<Dog> Repository::listDogsRepo() {
	/*
		Returns the list of all the dogs
	*/

	return this->dyn_arr;
}

bool Repository::isEmpty(std::ifstream &f) {
	return f.peek() == std::ifstream::traits_type::eof();
}

void Repository::readFile() {
	std::ifstream fin(this->file);
	if (!this->isEmpty(fin)) {
		Dog d;
		while (fin >> d) {
			if (std::find(this->dyn_arr.begin(), this->dyn_arr.end(), d) == this->dyn_arr.end()) {
				this->dyn_arr.push_back(d);
			}
		}
		fin.close();
	} else {
		std::string breeds[] = {"affenpinscher", "Afghan hound", "Airedale terrier", "Akita", "Alaskan Malamute",
								"American Staffordshire terrier", "American water spaniel", "Australian cattle dog",
								"Australian shepherd", "Australian terrier", "basenji", "basset hound", "beagle",
								"bearded collie",
								"Bedlington terrier", "Bernese mountain dog", "bichon frise", "black and tan coonhound",
								"bloodhound",
								"border collie", "border terrier", "borzoi", "Boston terrier", "bouvier des Flandres",
								"boxer",
								"briard",
								"Brittany", "Brussels griffon", "bull terrier", "bulldog", "bullmastiff",
								"cairn terrier",
								"Canaan dog",
								"Chesapeake Bay retriever", "Chihuahua", "Chinese crested", "Chinese shar-pei",
								"chow chow",
								"Clumber spaniel", "cocker spaniel", "collie", "curly-coated retriever", "dachshund",
								"Dalmatian",
								"Doberman pinscher", "English cocker spaniel", "English setter",
								"English springer spaniel",
								"English toy spaniel", "Eskimo dog", "Finnish spitz", "flat-coated retriever",
								"fox terrier",
								"foxhound",
								"French bulldog", "German shepherd", "German shorthaired pointer",
								"German wirehaired pointer",
								"golden retriever", "Gordon setter", "Great Dane", "greyhound", "Irish setter",
								"Irish water spaniel",
								"Irish wolfhound", "Jack Russell terrier", "Japanese spaniel", "keeshond",
								"Kerry blue terrier",
								"komondor", "kuvasz", "Labrador retriever", "Lakeland terrier", "Lhasa apso", "Maltese",
								"Manchester terrier", "mastiff", "Mexican hairless", "Newfoundland",
								"Norwegian elkhound",
								"Norwich terrier", "otterhound", "papillon", "Pekingese", "pointer", "Pomeranian",
								"poodle",
								"pug",
								"puli", "Rhodesian ridgeback", "Rottweiler", "Saint Bernard", "saluki", "Samoyed",
								"schipperke",
								"schnauzer", "Scottish deerhound", "Scottish terrier", "Sealyham terrier",
								"Shetland sheepdog",
								"shih tzu", "Siberian husky", "silky terrier", "Skye terrier",
								"Staffordshire bull terrier",
								"soft-coated wheaten terrier", "Sussex spaniel", "spitz", "Tibetan terrier", "vizsla",
								"Weimaraner",
								"Welsh terrier", "West Highland white terrier", "whippet", "Yorkshire terrier"};
		std::string names[] = {"Bella", "Luna", "Lucy", "Daisy", "Lola", "Sadie", "Molly", "Bailey", "Stella", "Maggie",
							   "Chloe", "Penny", "Nala", "Zoey", "Lily", "Coco", "Sophie", "Rosie", "Ellie", "Ruby",
							   "Piper", "Mia", "Roxy", "Gracie", "Millie", "Willow", "Lulu", "Pepper", "Ginger",
							   "Harley",
							   "Abby", "Winnie", "Nova", "Kona", "Riley", "Zoe", "Lilly", "Dixie", "Lady", "Izzy",
							   "Hazel",
							   "Layla", "Olive", "Charlie", "Sasha", "Maya", "Honey", "Athena", "Lexi", "Cali", "Annie",
							   "Belle", "Princess", "Phoebe", "Emma", "Ella", "Cookie", "Marley", "Callie", "Scout",
							   "Roxie", "Remi", "Minnie", "Maddie", "Dakota", "Leia", "Poppy", "Josie", "Harper",
							   "Mila",
							   "Angel", "Holly", "Ava", "Ivy", "Mocha", "Gigi", "Paisley", "Koda", "Cleo", "Penelope",
							   "Bonnie", "Missy", "Frankie", "Sugar", "Aspen", "Xena", "Shelby", "Fiona", "Dolly",
							   "Georgia", "Shadow", "Delilah", "Peanut", "Grace", "Rose", "Skye", "Pearl", "Jasmine",
							   "Juno", "Trixie", "Max", "Charlie", "Milo", "Buddy", "Rocky", "Bear", "Leo", "Duke",
							   "Teddy",
							   "Tucker", "Beau", "Oliver", "Jack", "Winston", "Ollie", "Toby", "Jax", "Blue", "Finn",
							   "Louie", "Murphy", "Loki", "Moose", "Gus", "Bruno", "Ace", "Apollo", "Hank", "Archie",
							   "Kobe", "Henry", "Thor", "Simba", "Bailey", "Scout", "Diesel", "Jake", "Lucky", "Buster",
							   "Otis", "Jackson", "Benny", "Chewy", "Jasper", "Oscar", "Bandit", "Rex", "Oreo", "Riley",
							   "Baxter", "Cody", "Coco", "Rocco", "Tank", "Prince", "Ranger", "King", "Marley",
							   "Roscoe",
							   "Sam", "Oakley", "Copper", "Gizmo", "Chase", "Luke", "Boomer", "Bruce", "Frankie",
							   "Chance",
							   "Rusty", "Hunter", "Ozzy", "Tyson", "Romeo", "Rudy", "Mac", "Bubba", "Peanut", "Kai",
							   "Chico", "Joey", "Atlas", "Goose", "Samson", "Chief", "Levi", "Titan", "Frank", "Axel",
							   "Brutus", "Ghost", "Brady", "Cosmo", "Scooby", "Chip", "Chester", "Wally", "Rufus",
							   "Dash",
							   "Louis"};
		std::string photos[] = {"https://upload.wikimedia.org/wikipedia/commons/d/d9/Collage_of_Nine_Dogs.jpg",
								"https://i.ytimg.com/vi/SfLV8hD7zX4/maxresdefault.jpg",
								"https://www.healthypawspetinsurance.com/Images/V3/DogAndPuppyInsurance/Dog_CTA_Desktop_HeroImage.jpg",
								"https://www.cesarsway.com/sites/newcesarsway/files/styles/large_article_preview/public/Natural-Dog-Law-2-To-dogs%2C-energy-is-everything.jpg?itok=Z-ujUOUr",
								"https://s3.amazonaws.com/cdn-origin-etr.akc.org/wp-content/uploads/2017/11/13001000/Beagle-On-White-01-400x267.jpg",
								"https://www.cesarsway.com/sites/newcesarsway/files/styles/large_article_preview/public/Common-dog-behaviors-explained.jpg?itok=FSzwbBoi",
								"https://www.nationalgeographic.com/content/dam/animals/thumbs/rights-exempt/mammals/d/domestic-dog_thumb.jpg",
								"https://vetstreet.brightspotcdn.com/dims4/default/54186d0/2147483647/thumbnail/590x420/quality/90/?url=https%3A%2F%2Fvetstreet-brightspot.s3.amazonaws.com%2F40%2F58%2F3bc5c01c4cdb8a0581681831faa9%2Fgreat-dane-shaking-paw-thinkstockphotos-522650067-590.jpg",
								"https://s7d1.scene7.com/is/image/PETCO/puppy-090517-dog-featured-355w-200h-d",
								"https://www.what-dog.net/Images/faces2/scroll001.jpg",
								"https://images.pexels.com/photos/356378/pexels-photo-356378.jpeg?auto=compress&cs=tinysrgb&h=350",
								"https://www.guidedogs.org/wp-content/uploads/2018/01/Mobile.jpg",
								"https://pbs.twimg.com/profile_images/846146544072101888/0sLpdiu1_400x400.jpg",
								"https://www.bluecross.org.uk/sites/default/files/assets/images/20311lpr.jpg",
								"https://dynaimage.cdn.cnn.com/cnn/q_auto,w_1024,c_fill,g_auto,h_576,ar_16:9/http%3A%2F%2Fcdn.cnn.com%2Fcnnnext%2Fdam%2Fassets%2F180316113418-travel-with-a-dog-3.jpg",
								"https://www.what-dog.net/Images/faces2/scroll0015.jpg",
								"http://cdn.akc.org/content/article-body-image/housetrain_adult_dog_hero.jpg",
								"https://pbs.twimg.com/profile_images/948761950363664385/Fpr2Oz35_400x400.jpg",
								"https://boygeniusreport.files.wordpress.com/2016/11/puppy-dog.jpg?quality=98&strip=all&w=782",
								"https://static-cdn.jtvnw.net/jtv_user_pictures/hsdogdog-profile_image-5550ade194780dfc-300x300.jpeg",
								"https://cdn.psychologytoday.com/sites/default/files/styles/article-inline-half/public/field_blog_entry_images/2018-02/vicious_dog_0.png?itok=nsghKOHs",
								"http://www.dogbazar.org/wp-content/uploads/2014/09/british-bull-dog-puppies.jpg",
								"https://s3.amazonaws.com/cdn-origin-etr.akc.org/wp-content/uploads/2017/11/13001815/Alaskan-Malamute-On-White-03-400x267.jpg",
								"http://r.ddmcdn.com/w_830/s_f/o_1/cx_20/cy_1463/cw_2528/ch_1422/APL/uploads/2014/11/puppy-cam-veer-2893191.jpg",
								"https://www.guidedogs.org/wp-content/uploads/2015/05/Dog-Im-Not.jpg",
								"http://www.petmd.com/sites/default/files/small-dog-breeds.jpg",
								"https://media.mnn.com/assets/images/2018/03/Alex_Cearns_tiny_dog.JPG.653x0_q80_crop-smart.jpg",
								"https://upload.wikimedia.org/wikipedia/commons/thumb/e/ea/Dog_coat_variation.png/220px-Dog_coat_variation.png",
								"https://i2-prod.walesonline.co.uk/incoming/article14453067.ece/ALTERNATES/s615b/JMP_SWA_230318Storm_Shayler-024_JPG.jpg",
								"https://i.ytimg.com/vi/C_lpU5DiJ0Y/maxresdefault.jpg",
								"http://www.franklincountydogs.com/adopt/assets/images/adoptable-size.jpg",
								"https://ksrpetcare.com/wp-content/uploads/2017/04/41059-Cute-Yellow-Labrador-puppy-in-play-bow-white-background.jpg",
								"https://i.kinja-img.com/gawker-media/image/upload/s--WFkXeene--/c_scale,f_auto,fl_progressive,q_80,w_800/ol9ceoqxidudap8owlwn.jpg",
								"https://s7d2.scene7.com/is/image/PetSmart/SV0401_CATEGORY_HERO-Dog-Dog-20160818?$SV0401$",
								"https://static.domain.com.au/domainblog/uploads/2018/01/28000029/2_h0osln.jpg",
								"https://assets3.thrillist.com/v1/image/2724237/size/tmg-article_tall;jpeg_quality=20.jpg",
								"https://s3.amazonaws.com/petfinder-us-east-1-petimages-prod/organization-photos/36234/36234-3.jpg?bust=2018-02-10+04%3A34%3A00",
								"https://dogshome.com/wp-content/uploads/animalimages//1042080/8ecc64fb425941ba88ed86a847c59b13-1519257095-1519257099_srch.jpg",
								"http://i.dailymail.co.uk/i/pix/2017/12/20/13/477ACA2400000578-0-image-a-61_1513778255742.jpg",
								"https://www.gov.ca.gov/wp-content/uploads/2018/03/First-Dog.jpg",
								"https://www.what-dog.net/Images/faces2/scroll009.jpg",
								"https://cdn.britannica.com/300x500/55/31555-131-240223FB.jpg",
								"http://cdn3-www.dogtime.com/assets/uploads/2014/08/file_23300_cane-corso-dog-breed.jpg",
								"https://d17fnq9dkz9hgj.cloudfront.net/uploads/2018/03/Pomeranian_01-390x203.jpeg",
								"https://i.ytimg.com/vi/ZgE-ZRvlIlk/maxresdefault.jpg",
								"https://vetstreet.brightspotcdn.com/dims4/default/5b3ffe7/2147483647/thumbnail/180x180/quality/90/?url=https%3A%2F%2Fvetstreet-brightspot.s3.amazonaws.com%2F8e%2F4e3910c36111e0bfca0050568d6ceb%2Ffile%2Fhub-dogs-puppy.jpg",
								"http://www.dogbazar.org/wp-content/uploads/2015/07/Boo-Puppie-For-Sale.jpg",
								"https://www.mercurynews.com/wp-content/uploads/2017/12/dog-junie_-bro-jorgensen.jpg",
								"http://cdn.skim.gs/images/mvjxbd3ialygojs0vzl8/top-10-small-breed-dogs",
								"https://www.cesarsway.com/sites/newcesarsway/files/styles/large_article_preview/public/Dog-bite-prevention.jpg?itok=3N2KTNkP",
								"https://media2.s-nbcnews.com/i/newscms/2016_43/1170500/hotdog-taco-dog-today-161029-tease_845d920c7ea63371a9bf48203d22036f.jpg",
								"https://s.hswstatic.com/gif/dog-9.jpg",
								"https://cdn.vox-cdn.com/thumbor/p0iNC-9SOsw9bc-DWA5IHw0VGoQ=/0x0:648x420/1200x800/filters:focal(273x159:375x261):no_upscale()/cdn.vox-cdn.com/uploads/chorus_image/image/58527051/gucci.0.gif",
								"https://lookaside.fbsbx.com/lookaside/crawler/media/?media_id=45564118207",
								"http://www.guinnessworldrecords.com/Images/Longest-tail-on-a-dog_tcm25-458597.jpg",
								"https://www.petinsurance.com/images/VSSimages/consumer/v5/banner_dog_insurance.jpg",
								"https://www.bluecross.org.uk/sites/default/files/assets/images/xylitol%20slice.jpg",
								"https://media3.giphy.com/media/mokQK7oyiR8Sk/giphy.gif",
								"https://news.nationalgeographic.com/content/dam/news/2017/08/19/waq-cats-dogs/waq-cat-dog-1.jpg",
								"https://cdn.vox-cdn.com/thumbor/wng90rt7pFT3o_oPRNV21iK-2x8=/0x0:4560x3041/1200x800/filters:focal(1916x1157:2644x1885)/cdn.vox-cdn.com/uploads/chorus_image/image/58504395/911428568.jpg.0.jpg",
								"https://d1o50x50snmhul.cloudfront.net/wp-content/uploads/2018/03/29155020/gettyimages-604576373-800x533.jpg",
								"http://static4.uk.businessinsider.com/image/58a83d6edd089576288b47c9/a-navy-seal-explains-what-to-do-if-youre-attacked-by-a-dog.jpg",
								"https://www.what-dog.net/Images/faces2/scroll006.jpg",
								"https://img.buzzfeed.com/buzzfeed-static/static/2017-04/25/4/enhanced/buzzfeed-prod-fastlane-01/enhanced-23831-1493109569-1.jpg",
								"https://d17fnq9dkz9hgj.cloudfront.net/uploads/2012/11/150838553-tips-for-first-30-days-dog-632x475.jpg",
								"https://i.ytimg.com/vi/IHIbg3zHJ20/maxresdefault.jpg",
								"https://s.abcnews.com/images/US/160825_vod_orig_historyofdogs_16x9_992.jpg",
								"https://cbsnews2.cbsistatic.com/hub/i/r/2015/02/27/dc63bf50-05ee-4733-9217-4718ee9c81fe/resize/620x465/cb60f988990627112be9a03525f66c34/labrador-retriever1istock.jpg",
								"http://a57.foxnews.com/images.foxnews.com/content/fox-news/lifestyle/2017/12/01/dog-who-attempted-to-escape-shelter-in-viral-video-gets-adopted/_jcr_content/par/featured_image/media-0.img.jpg/931/524/1512148563312.jpg?ve=1&tl=1&text=big-top-image",
								"http://www.readersdigest.ca/wp-content/uploads/2012/09/komondor-strangest-looking-dog-breeds.jpg",
								"http://www.dog10kgenomes.org/images/01.jpg",
								"https://www.rd.com/wp-content/uploads/2017/08/00_dog_Superpowers-All-Dogs-Have-that-Prove-They%E2%80%99re-Cooler-Than-Humans_572584759_Svetography-1024x683.jpg",
								"https://thenypost.files.wordpress.com/2018/05/180516-woman-mauled-by-angry-wiener-dogs-feature.jpg?quality=90&strip=all&w=618&h=410&crop=1",
								"https://lookaside.fbsbx.com/lookaside/crawler/media/?media_id=1443900315852048",
								"https://upload.wikimedia.org/wikipedia/commons/thumb/6/69/Dog_morphological_variation.png/300px-Dog_morphological_variation.png",
								"https://postmediacanoe.files.wordpress.com/2018/04/blacklab1000.jpg",
								"https://www.sddac.com/content/dam/sdc/das/images/aussie-shepherd.jpg",
								"https://www.petinsurance.com/images/dog-bone.png",
								"http://www.cheatsheet.com/wp-content/uploads/2017/05/doberman-dog-outdoors-640x427.jpg",
								"https://bowwowinsurance.com.au/wp-content/uploads/2017/03/chihuahua-mating-dogs-sex-humping.jpg",
								"https://www.telegraph.co.uk/content/dam/news/2018/01/25/TELEMMGLPICT000144075850_trans_NvBQzQNjv4BqtBZSUvGe3rsJxi0SXUlx8GyKXiPqmHbXbjFyMKQyNKk.jpeg?imwidth=450",
								"https://img.huffingtonpost.com/asset/5b1ac3fe1a00002700ce0fe3.jpeg?cache=hd8spmkjbl&ops=1910_1000",
								"https://www.royalcanin.com/~/media/Royal-Canin/Product-Categories/dog-maxi-landing-hero.ashx",
								"https://peopledotcom.files.wordpress.com/2018/02/dog-monkey.jpg",
								"https://www.mccanndogs.com/images/shutterstock_492831022.jpg",
								"https://www.gannett-cdn.com/-mm-/2e3fe0b3ef31b51ed31002079cddbd00082b19a1/c=0-0-720-960&r=537&c=0-0-534-712/local/-/media/2018/03/23/Cincinnati/Cincinnati/636573867887450748-warren-dog.jpg",
								"https://cdn.pixabay.com/photo/2016/11/01/23/38/beach-1790049_960_720.jpg",
								"https://cloud.lovinmalta.com/images/uploads/2017/12/_blogWide/gre_171220_152524.png?mtime=20171220152524",
								"https://article.images.consumerreports.org/prod/content/dam/CRO%20Images%202018/Health/March/CR-Health-InlineHero-toxic-food-for-dogs-0318",
								"http://animal-dream.com/data_images/dog/dog10.jpg",
								"http://img.zergnet.com/1240050_300.jpg",
								"https://www.purina.com/sites/g/files/auxxlc196/files/styles/kraken_generic_max_width_240/public/WORKING_Anatolian-Shepherd-Dog.jpg?itok=KF0dlL6d",
								"https://amp.businessinsider.com/images/56c4bd4e6e97c627008b7bcb-750-633.jpg",
								"https://i.guim.co.uk/img/media/ef861f8d2fa426e16660d64f2bc5cd70441c6566/0_219_5278_3167/master/5278.jpg?w=1200&h=630&q=55&auto=format&usm=12&fit=crop&crop=faces%2Centropy&bm=normal&ba=bottom%2Cleft&blend64=aHR0cHM6Ly91cGxvYWRzLmd1aW0uY28udWsvMjAxOC8wMS8zMS9mYWNlYm9va19kZWZhdWx0LnBuZw&s=f4c0d1ccf6dd044b60c8020ed6d2f295",
								"https://hips.hearstapps.com/hmg-prod.s3.amazonaws.com/images/dogzoom7-1520883582.jpg?crop=1xw:1xh;center,top&resize=480:*",
								"https://s7d1.scene7.com/is/image/PETCO/category-dog-021318-image-580w-270h-d?$transparent_unsized$",
								"http://interestpost.com/wp-content/uploads/2017/04/mood-boosting.jpeg",
								"https://cdn.psychologytoday.com/sites/default/files/styles/article-inline-half/public/field_blog_entry_images/2018-02/cloned_dogs_mdorottya_123rf.png?itok=yiaSkqQA",
								"https://www.petcentric.com/assets/img/breeds/dogs/beagle.jpg",
								"https://www.sciencealert.com/images/SmartDogs2.jpg",
								"https://bowwowinsurance.com.au/wp-content/uploads/2015/12/bernese-mountain-dog-thumbnail.jpg",
								"https://peopledotcom.files.wordpress.com/2017/02/dog-in-wood.jpg",
								"https://cdn.pixabay.com/photo/2016/02/19/15/46/dog-1210559_960_720.jpg",
								"https://e3.365dm.com/17/12/750x563/skynews-samoyed-dog-puppy_4189231.jpg?20171221201448",
								"http://channel.nationalgeographic.com/exposure/content/photo/photo/2103970_how-long-is-too-long-to-leave-your-dog-alone_fv2fyj4mbywqvzaz4k27i3sk3c2ptt7hevj74cagwi5qbj2htjuq_757x425.jpg",
								"https://www.telegraph.co.uk/content/dam/news/2018/04/25/TELEMMGLPICT000146033712_trans_NvBQzQNjv4BqpdquQA-gsM6cBCkZN_HIiLMSC6xrnuJ9Yuq4JszxuIk.jpeg?imwidth=450",
								"https://media.mnn.com/assets/images/2018/03/Alex_Cearns_dog.JPG.653x0_q80_crop-smart.jpg",
								"https://hips.hearstapps.com/ghk.h-cdn.co/assets/16/08/3200x1600/landscape-gettyimages-530330473-1.jpg?resize=480:*",
								"https://www.handicappedpets.com/wp-content/uploads/2017/05/male-wrap-1.jpg",
								"https://upload.wikimedia.org/wikipedia/commons/thumb/a/ae/Wilde_huendin_am_stillen.jpg/220px-Wilde_huendin_am_stillen.jpg",
								"https://s3.amazonaws.com/cdn-origin-etr.akc.org/wp-content/uploads/2017/11/12233437/Entlebucher-Mountain-Dog-On-White-01.jpg",
								"https://static1.squarespace.com/static/55e48783e4b0b05d86d82227/56fdf38c746fb9c9ad4bf4ce/59d51a91a803bbe8c04dd3f5/1512322762227/IMG_0313.JPG?format=500w",
								"https://www.cesarsway.com/sites/newcesarsway/files/styles/large_article_preview/public/How%20to%20calm%20a%20hyper%20dog.jpg?itok=Vg7ueySi",
								"http://cdn2-www.dogtime.com/assets/uploads/2011/01/file_23020_dachshund-dog-breed.jpg",
								"http://www.cheatsheet.com/wp-content/uploads/2017/04/Four-puppies-of-Japanese-akita-inu-breed-dog.jpg",
								"http://www.genconnect.com/wp-content/uploads/2012/08/help-dog.jpg",
								"https://i.ytimg.com/vi/4OLJe8iMLg4/hqdefault.jpg",
								"https://images-na.ssl-images-amazon.com/images/I/81HQzfVZkKL._SL1500_.jpg",
								"https://www.quickanddirtytips.com/sites/default/files/images/4448/Dog_Chew.jpg",
								"https://mediaassets.abc15.com/photo/2017/10/17/knxv%20cody%20dog_1508285664667_69047089_ver1.0_640_480.jpg",
								"https://thumbs-prod.si-cdn.com/py5a_dlu0L9V-Ff2LPfynGOsS5U=/1072x720/filters:no_upscale()/https://public-media.smithsonianmag.com/filer/20/7b/207ba889-20d5-40ed-97d2-46a806a658e7/screen_shot_2018-03-12_at_31315_pm.png",
								"https://www.thesun.co.uk/wp-content/uploads/2017/10/gettyimages-590486672-e1508512743796.jpg?strip=all&w=960",
								"https://www.rd.com/wp-content/uploads/2018/04/shutterstock_778330930-760x506.jpg",
								"https://www.petcentric.com/assets/img/breeds/dogs/beauceron.jpg",
								"http://r.ddmcdn.com/w_830/s_f/o_1/cx_0/cy_220/cw_1255/ch_1255/APL/uploads/2014/11/dog-breed-selector-australian-shepherd.jpg",
								"https://media.newyorker.com/photos/59e62efaa3920b73fc39302c/master/w_727,c_limit/Tolentino-A-Poe-and-a-Neuroscientist-Consider-How-Dogs-Think.jpg",
								"https://media.petango.com/sms/photos/1686/29cdb7a2-4f0b-422e-916b-fa1eb1978c5d.jpg",
								"https://i.kinja-img.com/gawker-media/image/upload/s--4vlfc0Vs--/c_scale,f_auto,fl_progressive,q_80,w_800/zhdfbwvbc2miyqyaryl9.jpg",
								"https://sed.visionaustralia.org/sites/seda/files/images/dogs/hero.jpg?sfvrsn=0&size=35%25",
								"https://lookaside.fbsbx.com/lookaside/crawler/media/?media_id=1100202279999571",
								"https://www.what-dog.net/Images/faces2/FBShareImage.jpg",
								"https://thenypost.files.wordpress.com/2018/04/dog-yoga-is-a-thing.jpg?quality=90&strip=all&w=618&h=410&crop=1",
								"https://www.meradog.com/editor/_processed_/8/0/csm_dog-with-food_374ac42fff.jpg",
								"https://static1.squarespace.com/static/59d7eb2b268b96ed79bacaef/t/5a693f6fe4966b51f6ae4f51/1516846967497/Beagle.jpg?format=1500w",
								"https://s.hdnux.com/photos/67/00/47/14420420/3/920x920.jpg",
								"https://metrouk2.files.wordpress.com/2018/04/610794096-e1523542866250.jpg?w=748&h=598&crop=1",
								"https://gfnc1kn6pi-flywheel.netdna-ssl.com/wp-content/uploads/2017/05/girl-names-1024x563.jpg",
								"https://media.npr.org/assets/img/2017/02/15/gettyimages-635359428-306f60c59f85cbb9870282ed5f7ad6d8ba002d4c-s1000-c85.jpg",
								"https://www.dogspot.in/new/breed_engine/images/dog_images/kombai.jpg",
								"http://i.dailymail.co.uk/i/newpix/2018/04/30/23/4BB2AC7B00000578-0-image-a-26_1525128621796.jpg",
								"https://barkpost.com/wp-content/uploads/2015/10/reddit-dog-jokes-20.jpg",
								"https://www.bluecross.org.uk/sites/default/files/styles/thumbnail_pet/public/pets/1102793/434902.jpg?itok=fe5gnzwK",
								"https://media.petango.com/sms/photos/1686/d6714be0-18aa-498c-bc80-59e6aab01b93.jpg",
								"https://images-na.ssl-images-amazon.com/images/I/61QACVSp-%2BL._SY355_.jpg",
								"http://i0.kym-cdn.com/entries/icons/original/000/000/027/advicedog.jpg",
								"https://ewedit.files.wordpress.com/2018/02/ols4_dogs_042517_011.jpg?crop=0px%2C290px%2C2700px%2C1419px&resize=1200%2C630",
								"https://s7d2.scene7.com/is/image/PetSmart/SV0401_CATEGORY_HERO-PetsHotel-Dog-20160818?$SV0401$",
								"https://www.agent.media/wp-content/uploads/2017/02/01-Boo.jpg",
								"https://ajo.prod.reuters.tv/api/v2/img/5a822bd1e4b05ce65e85e059-1518480337244?width=640&location=LANDSCAPE&videoId=RCV004IT6",
								"http://static6.uk.businessinsider.com/image/5485effbdd089573688b45fb/9-science-backed-reasons-to-own-a-dog.jpg",
								"https://i.amz.mshcdn.com/2xXpy52DS30uKJBrQm-qI1JDAbc=/fit-in/1200x9600/https%3A%2F%2Fblueprint-api-production.s3.amazonaws.com%2Fuploads%2Fcard%2Fimage%2F454852%2Fc149fd02-3174-46f9-9b58-d7026cc5ada9.jpg",
								"http://d1bg7skqn1enc5.cloudfront.net/sads/photos/animal/2268/5a73ed2f9de3e_20180202044639000000_crop.jpg",
								"https://ichef.bbci.co.uk/news/660/cpsprodpb/FDD6/production/_100728946_catrelax.jpg",
								"https://timedotcom.files.wordpress.com/2017/08/dog.jpg",
								"https://static1.squarespace.com/static/55e48783e4b0b05d86d82227/56fdf38c746fb9c9ad4bf4ce/5a4bc0b9e2c4835a778e7ba9/1516741262959/IMG_0325.JPG",
								"https://media4.s-nbcnews.com/i/newscms/2018_02/2285561/180109-dog-listening-mn-1215_86fd9caebf17bddbf5310597b860cef9.jpg",
								"https://www.akc.org/wp-content/themes/akc/component-library/assets//img/welcome.jpg",
								"https://www.what-dog.net/Images/faces2/scroll0010.jpg",
								"https://www.soidog.org/sites/default/files/Sliders_Mobile_Cola.jpg",
								"https://upload.wikimedia.org/wikipedia/commons/thumb/d/d6/GermanShep1_wb.jpg/220px-GermanShep1_wb.jpg",
								"https://www.purina.com/sites/g/files/auxxlc196/files/styles/kraken_generic_max_width_240/public/HERDING_Australian-Cattle-Dog.jpg?itok=Sw7bkqa_",
								"https://media.fox9.com/media.fox9.com/photo/2018/03/02/5%20P%20MISSING%20DOG%20FOUND%20DEAD_00.00.06.04_1520042792006.png_5029487_ver1.0_640_360.jpg",
								"https://www.rover.com/blog/wp-content/uploads/2017/09/dog-holding-own-leash-HERO-1024x573.jpg",
								"https://cdn10.bostonmagazine.com/wp-content/uploads/sites/2/2018/04/spencer-marathon-dog-1.jpg",
								"https://media4.s-nbcnews.com/i/newscms/2017_17/1210958/23-year-old-dog-today-170428-tease_fa167e6cdcf9343342b16f1116b3fcf3.jpg",
								"https://news.nationalgeographic.com/content/dam/news/2018/04/28/waq-dogs-and-storms/01-waq-dogs-and-storms-NationalGeographic_1468936.jpg",
								"https://www.dogstrust.org.uk/sponsor/_dogs/bubba-assets/v235_bubba1.jpg",
								"http://cdn0.wideopenpets.com/wp-content/uploads/2016/08/bigstock-Beagle-Dog-Lying-On-Carpet-In-110956046-770x405.jpg",
								"https://www.sciencedaily.com/images/2017/10/171019100944_1_900x600.jpg",
								"http://www.sciencemag.org/sites/default/files/styles/inline__450w__no_aspect/public/dogbreed_16x9.jpg?itok=UZ1-swsx",
								"https://cdn.pixabay.com/photo/2015/03/26/09/54/pug-690566_960_720.jpg",
								"https://sosd.org.sg/wp-content/uploads/2017/09/Batman.jpg",
								"https://img.webmd.com/dtmcms/live/webmd/consumer_assets/site_images/articles/health_tools/long_living_dog_breeds_slideshow/thinkstock_rf_photo_of_labrador_retriever.jpg",
								"http://www.dogster.com/wp-content/uploads/2017/11/A-dog-looking-up-confused-nervous-anxious.jpg",
								"https://i.guim.co.uk/img/media/1dbd0764efed7e86f4a21027aa0b32ba2b31ac8c/0_110_4252_2552/500.jpg?q=55&auto=format&usm=12&fit=max&s=423ea5e75dbc2325f8ff4d096b715e0c",
								"http://lightswitchtimer.co.uk/wp-content/uploads/2013/12/lights-for-pets.jpg",
								"https://urbanmilwaukee.com/wp-content/uploads/2017/06/Too-cute-doggone-it-video-playlist-1.jpg",
								"https://www.aspca.org/sites/default/files/dog-care_dog-bite-prevention_thumb.jpg",
								"https://vetstreet.brightspotcdn.com/dims4/default/7316536/2147483647/crop/0x0%2B0%2B0/resize/180x180/quality/90/?url=https%3A%2F%2Fvetstreet-brightspot.s3.amazonaws.com%2F56%2F7a0920b3ac11e092fe0050568d634f%2Ffile%2Fhub-dogs-senior.jpg",
								"https://4.imimg.com/data4/CG/SD/MY-23834646/pets-dog-250x250.jpg",
								"http://image.shutterstock.com/z/stock-photo-beagle-dog-in-front-of-a-white-background-76764031.jpg",
								"https://www.rosehipvitalcanine.com.au/wp-content/uploads/2012/11/Super_Sausage_Dog.jpg",
								"https://img.purch.com/w/660/aHR0cDovL3d3dy5saXZlc2NpZW5jZS5jb20vaW1hZ2VzL2kvMDAwLzA5Ny8xMTgvb3JpZ2luYWwvY2F0LWRvZy5qcGc=",
								"https://www.popsci.com/sites/popsci.com/files/images/2017/12/dog_eating_chocolate.jpg",
								"http://thisdogslife.co/wp-content/uploads/2014/12/thedogist-on-Instagram_TK.png",
								"http://theilovedogssite.com/wp-content/uploads/2015/01/4577137586_5f4cf7fbd3_z.jpg",
								"https://dogshome.com/wp-content/uploads/animalimages//1013871/6123750993cc4295b03506c4da595e9c-1517450065-1517450078_srch.jpg",
								"http://cdn-img.health.com/sites/default/files/styles/medium_16_9/public/migration/img/web/2015/07/dog-workout-opener-400x400.jpg?itok=kAnl65Nb",
								"https://www.royalcanin.com/~/media/Royal-Canin/Product-Categories/dog-puppy-landing-hero.ashx",
								"http://petsarena.com.ng/wp-content/uploads/2017/10/hero-dog.jpg",
								"https://www.hillspet.co.za/content/dam/cp-sites/hills/hills-pet/en_us/img/care/HP_PCC_lg_dog_routine_care_hero.jpg",
								"https://hips.hearstapps.com/ghk.h-cdn.co/assets/16/08/3200x1600/landscape-gettyimages-122137874-1.jpg?resize=768:*",
								"https://www.bluecross.org.uk/sites/default/files/assets/images/Distemper%201.jpg",
								"https://static.wixstatic.com/media/c7acecb7fdc042f3951cac9b867800ad.jpeg",
								"http://r.ddmcdn.com/s_f/o_1/cx_278/cy_0/cw_720/ch_720/w_720/APL/uploads/2017/12/ittakesavillage.jpg",
								"https://www.cdc.gov/healthypets/images/aggressive-dog.jpg",
								"https://www.teacupdogdaily.com/wp-content/uploads/2016/03/Teacup-Maltipoo-Dog-Breed-Emily.jpg",
								"https://content.rspca.org.uk/cmsprd/Satellite?blobcol=urldata&blobkey=id&blobtable=MungoBlobs&blobwhere=1232988236452&ssbinary=true",
								"https://www.sciencedaily.com/images/2018/03/180306115803_1_540x360.jpg",
								"https://casper.imgix.net/product/dog-mattress/ugc/shelly.jpg?auto=compress%2Cformat&q=65&w=380",
								"https://www.rd.com/wp-content/uploads/2018/04/shutterstock_693756292.jpg",
								"https://a-z-animals.com/media/animals/images/470x370/dog5.jpg",
								"https://static1.squarespace.com/static/55e48783e4b0b05d86d82227/56fdf38c746fb9c9ad4bf4ce/5a4bb8e30d929769938402c5/1515003464427/IMG_0293.JPG",
								"http://www.dogster.com/wp-content/uploads/2017/11/A-retriever-dog-licking-his-lips-and-eating.jpg",
								"https://pmdvod.nationalgeographic.com/NG_Video/24/506/smpost_1512590815348.jpg",
								"https://static.boredpanda.com/blog/wp-content/uploads/2018/01/Molly-5a65a1d189b95-png__880.jpg",
								"http://pethealthsupplements.com.au/wp-content/uploads/2015/06/tumblr_static_mom-dog-with-puppies.jpg",
								"https://i2-prod.mirror.co.uk/incoming/article8553582.ece/ALTERNATES/s1200/pomdog-pikachu.png",
								"https://media4.s-nbcnews.com/i/MSNBC/Components/Video/201804/nn_kda_petsmart_dog_deaths_controversy_180409_1920x1080.jpg",
								"https://cdn.thewirecutter.com/wp-content/uploads/2018/03/dog-toys-blog-lowres-3.jpg",
								"https://www.aspca.org/sites/default/files/dog-care_common-dog-behavior-problems_destructive-chewing_main-image.jpg",
								"https://aussiedog.com.au/wp-content/uploads/2017/08/aussie-dog-products-video.jpg",
								"https://cdn4.list25.com/wp-content/uploads/2015/02/Large_dog.jpg",
								"https://peopledotcom.files.wordpress.com/2018/06/baby-talk.jpg",
								"https://s3.amazonaws.com/cdn-origin-etr.akc.org/wp-content/uploads/2017/11/13001904/Akita-On-White-01-400x267.jpg",
								"http://www.dogswest.com/dogswest/img/breeder.jpg",
								"https://s7d2.scene7.com/is/image/PetSmart/PB1201_STORY_CARO-Authority-HealthyOutside-DOG-20160818?$PB1201$",
								"http://cdn.crownmediadev.com/b1/b8/dcdd338f4534b22f6525eada1d80/misha-seniordog-2.jpg",
								"http://hanslodge.com/images2018/dog-images/dog-images-29.jpg",
								"http://www.co.livingston.state.ny.us/ImageRepository/Document?documentID=6008",
								"https://www.dogslife.com.au/wp-content/uploads/2016/07/Slide-option-2.jpg",
								"https://usatftw.files.wordpress.com/2018/02/usp_news__westminster_kennel_club_dog_show_97397246.jpg?w=1000&h=705",
								"http://a57.foxnews.com/images.foxnews.com/content/fox-news/health/2017/12/27/china-clones-first-gene-edited-dog-but-its-sentenced-to-die-heart-disease/_jcr_content/par/featured_image/media-0.img.jpg/931/524/1514395122840.jpg?ve=1&tl=1&text=big-top-image",
								"https://media.npr.org/assets/img/2018/02/14/ap_18045200151993_wide-3b569dc90592c25cca9f0cc5a14a48ac55f743bf.jpg?s=1400",
								"http://0d02bf0b01928fa52b3d-dac3d8c6e89315cfc496dc0e1896ceb6.r86.cf1.rackcdn.com/Dog-Haus_Banner_Haus-Burger_the-Freiburger_01.jpg",
								"https://www.pets4homes.co.uk/images/dogs_hero.png",
								"https://img.buzzfeed.com/buzzfeed-static/static/2017-08/9/11/enhanced/buzzfeed-prod-fastlane-02/enhanced-1731-1502293831-8.jpg?downsize=715:*&output-format=auto&output-quality=auto",
								"http://www.insidedogsworld.com/wp-content/uploads/2016/09/Dog-happiness-1.jpg",
								"https://www.what-dog.net/Images/faces2/scroll005.jpg",
								"https://d2kwjcq8j5htsz.cloudfront.net/2015/12/02144203/dog-strawberry-TS-539120524.jpg",
								"https://www.what-dog.net/Images/faces2/scroll002.jpg",
								"https://media.petango.com/sms/photos/1686/896bd0b3-ee36-4e5e-8257-5b782eb96ea6.jpg",
								"http://cdn.skim.gs/images/c_fill,dpr_1.0,f_auto,fl_lossy,h_391,q_auto,w_695/fajkx3pdvvt9ax6btssg/20-of-the-cutest-small-dog-breeds-on-the-planet",
								"https://www.guidedogsvictoria.com.au/wp-content/uploads/2016/07/guide-dogs-mobility.jpg",
								"https://www.therapydogs.com/wp-content/uploads/2017/06/puppy.jpg",
								"http://www.diamondbackdrugs.com/wp-content/uploads/2017/02/weimaraner-puppy-dog-snout-97082.jpeg",
								"https://i2-prod.mirror.co.uk/incoming/article9769854.ece/ALTERNATES/s615/PROD-Mixed-breed-lab-cross-8-week-old-puppy-in-farm-yard-near-Cochrane-AlbertajpgED.jpg",
								"http://beta.apdt.com/wp-content/uploads/2017/02/APDT-OG.jpg",
								"http://cdn.playbuzz.com/cdn/7820ec56-cd7d-487c-87ba-30ca87219dc4/f0ea119d-812d-40ac-b5b8-96564e451038.jpg",
								"https://s4.scoopwhoop.com/anj/indiandogs/65f2f70e-b219-4d30-b79d-5d8263379517.jpg",
								"https://www.dogstrustgifts.com/acatalog/80699.jpg",
								"https://metrouk2.files.wordpress.com/2017/10/83454906.jpg?w=620&h=412&crop=1",
								"https://www.telegraph.co.uk/content/dam/pets/2017/05/08/pitbull-xlarge.jpg",
								"https://www.guidedogs.com.au/sites/default/files/styles/content_inline/public/guide-dog-puppy_0.jpg?itok=0lSVk_c1",
								"http://dingo.care2.com/pictures/greenliving/uploads/2017/10/Happy-small-dog.jpg",
								"https://article.images.consumerreports.org/prod/content/dam/CRO%20Images%202017/Electronics/April/CR-Electronics-Inline-Pet-Portraits-04-03",
								"http://dynaimage.cdn.turner.com/gns/gns/e_trim/180213130413-westminster-dog-show-5.jpg",
								"https://s.abcnews.com/images/US/cute-dog-gty-jpo-171116_4x3_992.jpg",
								"https://images-na.ssl-images-amazon.com/images/I/71KYNVRjhOL._SL1443_.jpg",
								"https://www.rspca.org.uk/webContent/staticImages/SectionImages/Dogs.jpg",
								"https://cbsnews3.cbsistatic.com/hub/i/r/2016/02/22/be8b2266-8910-42e2-bf5e-ad6b7baa761d/resize/620x465/ec2305df5891facb4f186decd1937b47/istock000014944804large.jpg",
								"https://pmdvod.nationalgeographic.com/NG_Video/753/659/smpost_1521820141073.jpg",
								"https://s.hswstatic.com/gif/top-10-naughtiest-pets-130214-chihuahua.jpg",
								"http://cdn.iflscience.com/images/89e93637-adbb-507c-bc8b-d94a1f3eec13/content-1508417557-shutterstock-519101614.jpg",
								"https://bowwowinsurance.com.au/wp-content/uploads/2014/12/white-maltese-700x700.jpg",
								"http://www.cheatsheet.com/wp-content/uploads/2017/04/Puppy-Boxer-Dog.jpg",
								"https://static.businessinsider.com/image/5432c76b6da8114028e4abc7-400/image.jpg",
								"https://brightcove04pmdo-a.akamaihd.net/4221396001/4221396001_5769763726001_5769765297001-vs.jpg?pubId=4221396001&videoId=5769765297001",
								"https://i.ytimg.com/vi/1H6qWm2IGZ8/maxresdefault.jpg",
								"https://www.movies4kids.co.uk/wp-content/uploads/2017/04/ADogsPurpose_Clip_ChaseABall.jpg",
								"https://www.rd.com/wp-content/uploads/2018/04/shutterstock_598614479-760x506.jpg",
								"http://www.yourpurebredpuppy.com/dogbreeds/photos-MNOP/mixedbreeddogs9-large.jpg",
								"https://www.petmd.com/sites/default/files/salmonella-infection-dogs.jpg",
								"https://localtvkfor.files.wordpress.com/2018/01/promo339303724.jpg?quality=85&strip=all&w=1200",
								"https://www.rover.com/blog/wp-content/uploads/2016/09/DogMusicLead-600x340.jpg",
								"https://assets3.thrillist.com/v1/image/2757079/size/tmg-article_tall;jpeg_quality=20.jpg",
								"https://img.rasset.ie/000ee799-614.jpg?ratio=1.33",
								"https://vetstreet.brightspotcdn.com/dims4/default/cc1c07c/2147483647/crop/0x0%2B0%2B0/resize/180x180/quality/90/?url=https%3A%2F%2Fvetstreet-brightspot.s3.amazonaws.com%2F45%2Fa06040b3ac11e092fe0050568d634f%2Ffile%2Fhub-dogs-adult.jpg",
								"https://cdn.newsapi.com.au/image/v1/0a75db7c5b8946c90150cda9ecf3f310",
								"https://d3i6fh83elv35t.cloudfront.net/static/2018/04/cats-and-dogs_AdobeStock_84016419-1024x681.jpeg",
								"http://www.petguide.com/wp-content/uploads/2014/10/cutest-dog-breeds-main.jpg",
								"http://r.ddmcdn.com/s_f/o_1/cx_166/cy_0/cw_2130/ch_2130/w_720/APL/uploads/2018/01/35655_Max-0121-1.jpg",
								"http://www.lifetimewarrantyfence.com/wp-content/uploads/2015/04/how-to-keep-a-dog-from-getting-out-of-your-yard.png",
								"https://assets.bwbx.io/images/users/iqjWHBFdfxIU/it1CVDAvdCxI/v0/1200x800.jpg",
								"https://img.wennermedia.com/480-width/puppy-mills-8c9af2d6-754d-40ab-b0be-0554b1d255f1.jpg",
								"http://d1bg7skqn1enc5.cloudfront.net/sads/photos/animal/2403/5ae28fd0eb4a8_20180427024952000000_crop.jpg",
								"http://ejournalz.com/wp-content/uploads/2017/06/Dog-Care.jpg",
								"https://i0.wp.com/freedomguidedogs.org/wp-content/uploads/2018/01/cropped-Puppy-FGD-in-coat-transparent-1.png?fit=512%2C512&ssl=1",
								"http://www.dogster.com/wp-content/uploads/2017/08/An-embarrassed-dog.jpg",
								"http://www.petiquettedog.com/wp-content/uploads/2010/07/puppies_1.jpg",
								"https://i.guim.co.uk/img/media/d2fce9f340f97b2c8a8fba05aa064395657e9c62/0_193_5787_3472/master/5787.jpg?w=1200&h=630&q=55&auto=format&usm=12&fit=crop&crop=faces%2Centropy&bm=normal&ba=bottom%2Cleft&blend64=aHR0cHM6Ly91cGxvYWRzLmd1aW0uY28udWsvMjAxOC8wMS8zMS9mYWNlYm9va19kZWZhdWx0LnBuZw&s=d6acf4988f112bc56b2d19202b3d3f88",
								"http://www.doghaus.com/dh-uploads/home%20page%20images/Home%20Banner%20Images/Dog-Haus_Banner_Haus-Dog_Sooo-Cali_01.jpg",
								"http://otowndogrescue.com/wp-content/uploads/2013/09/dog3.png",
								"http://s7d9.scene7.com/is/image/AmericanApparel/f997wb2_lapis?defaultImage=/notavail&$ProductGrid2.5_3$",
								"https://thenypost.files.wordpress.com/2018/04/180404-family-killed-by-dog-feature.jpg?quality=90&strip=all&w=618&h=410&crop=1",
								"http://www.dogbreedplus.com/dog_names/images/puppy-dog-names.jpg",
								"https://static1.squarespace.com/static/59d7eb2b268b96ed79bacaef/t/5a4eab5de2c4837fbba13796/1517620552038/resource-guarding-dog.jpg",
								"https://media.wired.com/photos/5a9754f9d2c5f03d18982b22/master/w_1600,c_limit/browndog.jpg",
								"https://wtop.com/wp-content/uploads/2017/11/110817_dog_3-594x485.jpg",
								"https://img.webmd.com/dtmcms/live/webmd/consumer_assets/site_images/articles/health_tools/best_dog_breed_for_your_health_slideshow/getty_rm_photo_of_three_dogs_on_white.jpg",
								"https://img.grouponcdn.com/deal/GWD9f9dsvgA8qzDKKiTThstT7aU/GW-1500x900/v1/c700x420.jpg",
								"https://cdn.lifehack.org/wp-content/uploads/2014/09/10-Reasons-Why-Dogs-are-Mans-Best-Friend.jpg",
								"https://i5.walmartimages.com/dfw/4ff9c6c9-a77b/k2-_864ef38f-4c7e-427e-8a3c-7415272c6919.v1.jpg",
								"https://upload.wikimedia.org/wikipedia/commons/thumb/7/7e/Bow_bow.jpg/220px-Bow_bow.jpg",
								"https://boygeniusreport.files.wordpress.com/2017/05/dog.jpg?quality=98&strip=all&w=782",
								"https://i.kinja-img.com/gawker-media/image/upload/s--pRSisy9n--/c_scale,f_auto,fl_progressive,q_80,w_800/qcsny75ocrnawafhs8pj.jpg",
								"https://www.cesarsway.com/sites/newcesarsway/files/styles/large_article_preview/public/Why%20dogs%20eat%20grass_0.jpg?itok=fu5yHnol",
								"https://static1.squarespace.com/static/55e48783e4b0b05d86d82227/56fdf38c746fb9c9ad4bf4ce/59aa10e09f7456899e3660d3/1521273031390/Donnie.jpg?format=500w",
								"http://www.hedinghamhounds.co.uk/wp-content/uploads/2016/02/animal-dog-pet-bulldog.jpg",
								"https://usercontent1.hubstatic.com/7968066.jpg"};

		bool adopted[] = {false, true};
		srand((unsigned) time(0));
		for (int i = 0; i < 30; ++i) {
			int rand_breed = (rand() % (sizeof(breeds) / sizeof(*breeds))), rand_name = (rand() %
																						 (sizeof(names) /
																						  sizeof(*names)));
			while (checkDogExiNameBreedRepo(breeds[rand_breed], names[rand_name])) {
				rand_breed = (rand() % (sizeof(breeds) / sizeof(*breeds)));
				rand_name = (rand() % (sizeof(names) / sizeof(*names)));
			}
			Dog dog = Dog(breeds[rand_breed], names[rand_name], (rand() % 50) + 1,
						  photos[(rand() % (sizeof(photos) / sizeof(*photos)))], adopted[(rand() % 2)]);
			this->dyn_arr.push_back(dog);
		}
		this->writeFile();
	}
}

int Repository::checkDogExiNameBreedRepo(const std::string &breed, const std::string &name) {
	/*
		Checks if a dog already exists with the same breed and name

	 	breed - Breed of dog
	 	name - Name of dog
	*/

	for (auto i: this->dyn_arr) {
		if (breed == i.getBreed() && name == i.getName())
			return 1;
	}
	return 0;
}

void Repository::writeFile() {
	std::ofstream fout(this->file);
	for (const Dog &dog: this->dyn_arr) {
		fout << dog << "\n";
	}
	fout.close();
}

void Repository::initRepo() {
	this->readFile();
}

Repository::Repository(std::string &file) {
	this->file = file;
}

int Repository::checkDogExiNameBreedRepoAdd(const std::string &breed, const std::string &name) {
	for (auto &i: this->dyn_arr) {
		if (breed == i.getBreed() && name == i.getName())
			return 1;
	}
	return 0;
}

int Repository::checkDogExiNameBreedRepoDelUpd(int idx) {
	int j = 0;
	for (auto i: this->dyn_arr) {
		if (j == idx) return 1;
		++j;
	}
	return 0;
}

int Repository::checkDogExiNameBreedUserRepo(const std::string &breed, const std::string &name) {
	/*
		Checks if a dog already exists with the same breed and name

	 	breed - Breed of dog
	 	name - Name of dog
	*/

	int j = 0;
	for (const auto &i: this->dyn_arr) {
		if (breed == i.getBreed() && name == i.getName())
			return j;
		++j;
	}
	return -1;
}