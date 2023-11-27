#include <stdio.h>

typedef struct elem{
	int r,c,v;
	//r : row 
	//c : col
	//v : val
}elem;

typedef struct spm{
	elem arr[128];
	int nr,nc,n;
	//nr : no of rows in matrix
	//nc : no of col
	//n : no of elements in matirx
}spm;

struct spm add(struct spm a,struct spm b){
	struct spm ans;
	ans.nc=a.nc;
	ans.nr=a.nr;
	ans.n=0;

	for (int i=0;i<a.n;i++){
		ans.arr[ans.n++]=a.arr[i];
	}

	for (int i=0;i<b.n;i++){
		int flag=0;
		for (int j=0;j<ans.n;j++){
			if (((ans.arr[j]).r==(b.arr[i]).r) && (ans.arr[j]).c==(b.arr[i]).c){
				(ans.arr[j]).v += (b.arr[i]).v;
				flag=1;
				break;
			}
		}
		if (!flag){
			ans.arr[ans.n++]=b.arr[i];
		}
	}
	return ans;
}


struct spm sub(struct spm a,struct spm b){
        struct spm ans;
        ans.nc=a.nc;
        ans.nr=a.nr;
        ans.n=0;

        for (int i=0;i<a.n;i++){
                ans.arr[ans.n++]=a.arr[i];
        }

        for (int i=0;i<b.n;i++){
                int flag=0;
                for (int j=0;j<ans.n;j++){
                        if (((ans.arr[j]).r==(b.arr[i]).r) && (ans.arr[j]).c==(b.arr[i]).c){
                                (ans.arr[j]).v -= (b.arr[i]).v;
                                flag=1;
                                break;
                        }
                }
                if (!flag){
			(ans.arr[ans.n++]).r=(b.arr[i]).r;
			(ans.arr[ans.n]).c=(b.arr[i]).c;
                        ans.arr[ans.n].v=-((b.arr[i]).v);
                }
        }
        return ans;
}


int istranspose(spm a,spm b) {
    // dimension check
    if (a.nr != b.nc || a.nc != b.nr || a.n != b.n) {
        return 0; 
    }

    for (int i = 0; i < a.n; i++) {
        if ((a.arr[i]).r != (b.arr[i]).c || (a.arr[i]).c != (b.arr[i]).r || (a.arr[i]).v != (b.arr[i]).v) {
            return 0;
        }
    }

    return 1; 
}

void display(struct spm a){
	for (int i=0;i<a.n;i++){
		printf(" (%d %d %d) ",(a.arr[i]).r,(a.arr[i]).c,(a.arr[i]).v);
	}
	printf("NULL\n");
	return;
}

int issymm(struct spm a){
	return istranspose(a,a);
}

int main(){
	printf("SPARSE MATRIX USING ARRAY ADT\n");
	//struct spm*
	spm a = {
        {{0, 0, 2}, {1, 1, 3}, {2, 2, 4}},
        3, 3, 3
    };

    spm b = {
        {{0, 0, 1}, {1, 1, 2}, {2, 2, 5}},
        3, 3, 3
    };
	//b->arr[4]={{0,0,1},{1,1,2},{2,2,5},{3,3,3}};

	printf("A : \n");
	display(a);

	printf("B : \n");
        display(b);

	spm result=add(a,b);

	printf("A+B : \n");
        display(result);

	printf("A-B : \n");
        display(sub(a,b));

	printf("Is Transpose : A : %d\n",istranspose(a,b));
	printf("Is Symmetric : A : %d\n",issymm(a));

	return 0;
}

