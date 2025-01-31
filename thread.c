/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolan <yolan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:46:35 by yolan             #+#    #+#             */
/*   Updated: 2024/12/19 15:48:28 by yolan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;  // Déclaration du mutex global
int compteur = 0;       // Ressource partagée

void* fonctionThread(void* arg) {
    // Verrouiller le mutex avant d'accéder à la ressource partagée
    pthread_mutex_lock(&mutex);  
    for (int i = 0; i < 1000; i++) {
        compteur++;  // Modification de la ressource partagée
    }
    // Libérer le mutex après avoir terminé
    pthread_mutex_unlock(&mutex);  
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialisation du mutex
    pthread_mutex_init(&mutex, NULL);
    
    // Création de deux threads
    pthread_create(&thread1, NULL, fonctionThread, NULL);
    pthread_create(&thread2, NULL, fonctionThread, NULL);
    
    // Attente de la fin des deux threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Affichage du résultat final
    printf("Compteur final : %d\n", compteur);

    // Destruction du mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}