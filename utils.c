/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:31:11 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/04 21:10:03 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// 指定された閾値以上の時間が経過したかどうかをチェックする関数
int TimeHasPassed(struct timeval *start, long threshold) {
    struct timeval end;
    long elapsedTime;

    // 現在の時刻を取得
    gettimeofday(&end, NULL);

    // 経過時間をマイクロ秒単位で計算
    elapsedTime = (end.tv_sec - start->tv_sec) * 1000000L;
    elapsedTime += (end.tv_usec - start->tv_usec);

    // 経過時間が閾値を超えているかチェック
    if (elapsedTime > threshold) {
        // 閾値を超えていた場合は1を返す
        return 1;
    } else {
        // 閾値を超えていなかった場合は0を返す
        return 0;
    }
}
