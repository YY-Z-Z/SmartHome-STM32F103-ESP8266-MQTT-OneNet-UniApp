<template>
	<view class="content">
		<image class="logo" src="/static/logo.png"></image>
		<view class="text-area">
			<text class="title">{{token}}</text>
		</view>
	</view>
</template>

<script>
	// const {
	// 	createCommonToken
	// } = require('@/key.js')
	import { createCommonToken } from '@/key.js'
	
	export default {
		data() {
			return {
				title: 'Hello',
				token: '',
			}
		},
		onLoad() {
			const params = {
				author_key: 'a69f52mHLZE5D7UHRzerpTE72wEL58NL82ej9Smb85U=',
				version: '2022-05-01',
				user_id: 'ZL8V732K3u',
			}
			try {
			    this.token = createCommonToken(params);  
			    console.log('生成的 token:', this.token)
			} catch (error) {
			    console.error('生成失败:', error)
			}

		},
		methods: {

		}
	}
</script>

<style>
	.content {
		display: flex;
		flex-direction: column;
		align-items: center;
		justify-content: center;
	}

	.logo {
		height: 200rpx;
		width: 200rpx;
		margin-top: 200rpx;
		margin-left: auto;
		margin-right: auto;
		margin-bottom: 50rpx;
	}

	.text-area {
		display: flex;
		justify-content: center;
	}

	.title {
		font-size: 36rpx;
		color: #8f8f94;
	}
</style>
